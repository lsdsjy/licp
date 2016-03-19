#ifndef PREDICATE_H_INCLUDED
#define PREDICATE_H_INCLUDED

#include <string.h>
#include <ctype.h>

int isNumber(char *exp) {
    if ((*exp != '-') && !isdigit(*exp)) {
        return 0;
    }
    exp++;
    while (*exp) {
        if (!isdigit(*exp)) {
            return 0;
        }
        exp++;
    }
    return 1;
}

int isPrimitive(char *exp) {
    if (!exp) {
        return 0;
    }
    if (!strcmp(exp, "+") || !strcmp(exp, "-")
         || !strcmp(exp, "*") || !strcmp(exp, "/")
         || !strcmp(exp, "=") || !strcmp(exp, ">")
         || !strcmp(exp, "<") || !strcmp(exp, "not")) {
        return 1;
    }
    return 0;
}

int isLambda(char *exp) {
    if (!exp) {
        return 0;
    }
    return !strcmp(exp, "lambda");
}

int isDefinition(char *exp) {
    if (!exp) {
        return 0;
    }
    return !strcmp(exp, "define");
}

#endif // PREDICATE_H_INCLUDED
