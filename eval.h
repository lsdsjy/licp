#ifndef EVAL_H_INCLUDED
#define EVAL_H_INCLUDED

#include "environ.h"
#include "predicate.h"

#define BUF_SIZE 100

int parse(const char *exp, Node *self) {
    int start = 0, i = 0, len = strlen(exp), bp = 0;
    Node *cur = NULL;
    char buf[BUF_SIZE];
    while (i < len) {
        if (exp[i] == ' ' || exp[i] == '\t' || exp[i] == '\n' || exp[i] == ')') {
            if (bp) {
                buf[bp] = 0;
                cur = newNode(cur, self, buf);
                bp = 0;
            }
            if (exp[i] == ')') {
                return i;
            }
            i++;
        } else if (exp[i] == '(') {
            if (start) {
                cur = newNode(cur, self, NULL);
                i += parse(exp + i, cur) + 1;
            } else {
                start = 1;
                i++;
            }
        } else {
            buf[bp++] = exp[i++];
            start = 1;
        }
    }

    return i;
}

Value eval(Node *node, Environ *env);

Value evalPrimitive(Node *node, Environ *env) {
    if (!strcmp(node->exp, "+")) {
        return (Value){NUMBER, eval(node->next, env).num + eval(node->next->next, env).num};
    } else if (!strcmp(node->exp, "*")) {
        return (Value){NUMBER, eval(node->next, env).num * eval(node->next->next, env).num};
    } else if (!strcmp(node->exp, "-")) {
        return (Value){NUMBER, eval(node->next, env).num - eval(node->next->next, env).num};
    } else if (!strcmp(node->exp, "/")) {
        return (Value){NUMBER, eval(node->next, env).num / eval(node->next->next, env).num};
    } else if (!strcmp(node->exp, "=")) {
        return (Value){NUMBER, eval(node->next, env).num == eval(node->next->next, env).num};
    } else if (!strcmp(node->exp, ">")) {
        return (Value){NUMBER, eval(node->next, env).num > eval(node->next->next, env).num};
    } else if (!strcmp(node->exp, "<")) {
        return (Value){NUMBER, eval(node->next, env).num < eval(node->next->next, env).num};
    } else if (!strcmp(node->exp, "not")) {
        return (Value){NUMBER, !eval(node->next, env).num};
    }
    return nil;
}

Value evalSequence(Node *node, Environ *env) {
    while (node->next != NULL) {
        eval(node, env);
        node = node->next;
    }
    return eval(node, env);
}

//Value evalCondition(Node *node, Environ *env) {
//    ;
//}
//
//Value evalDefinition(Node *node, Environ *env) {
//    ;
//}

Value evalLambda(Node *node, Environ *env) {
    return (Value){PROCEDURE, 0, (Procedure){node->next, env}};
}

Value apply(Node *node, Environ *env);

Value eval(Node *node, Environ *env) {
    if (node->child) {
        node = node->child;
        if (isPrimitive(node->exp)) {
            return evalPrimitive(node, env);
//        } else if (isDefinition(node->exp)) {
//            evalDefinition(node, env);
        } else if (isLambda(node->exp)) {
            if (node->exp)
            return evalLambda(node, env);
        } else { //apply procedure
            return apply(node, env);
        }
    } else { //self-evaluating expressions
        if (isNumber(node->exp)) {
            return (Value){NUMBER, atoi(node->exp)};
//        } else if (isQuoted(node->exp)) {
//
        } else {
            return getValue(node->exp, env);
        }
    }

    return nil;
}

Value apply(Node *node, Environ *env) {
    Procedure proc = eval(node, env).proc;
    Node *arg = proc.node->child;
    Node *param = node->next;
    Environ *new_env = newEnviron(proc.env);
    while (arg) {
        defineValue(arg->exp, new_env, eval(param, env));
        arg = arg->next;
        param = param->next;
    }
    return evalSequence(proc.node->next, new_env);
}

#endif // EVAL_H_INCLUDED
