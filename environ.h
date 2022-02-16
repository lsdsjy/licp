#ifndef ENVIRON_H_INCLUDED
#define ENVIRON_H_INCLUDED

#include <string.h>
#include "node.h"

#define NAME_LEN 50

struct _Environment;
struct _ValList;

typedef struct {
    Node *node;
    struct _Environ *env;
} Procedure;

typedef struct {
    enum ValueType {
        NIL,
        NUMBER,
        PROCEDURE
    } type;
    int num;
    Procedure proc;
} Value;

Value nil = {NIL};

typedef struct _ValList {
    char name[NAME_LEN];
    Value value;
    struct _ValList *next;
} ValList;

typedef struct _Environ {
    ValList* vals;
    struct _Environ *parent;
} Environ;

Environ *newEnviron(Environ *parent) {
    Environ *env = (Environ *)malloc(sizeof(Environ));
    env->vals = NULL;
    env->parent = parent;
    return env;
}

Value *findValue(const char *name, Environ *env) {
    ValList *cur = env->vals;
    while (cur) {
        if (!strcmp(name, cur->name)) {
            return &cur->value;
        }
        cur = cur->next;
    }
    if (env->parent) {
        return findValue(name, env->parent);
    }
    return &nil;
}

void defineValue(const char *name, Environ *env, Value value) {
    ValList *val = (ValList *)malloc(sizeof(ValList));
    strcpy(val->name, name);
    val->value = value;
    val->next = env->vals;
    env->vals = val;
}

Value getValue(const char *name, Environ *env) {
    return *findValue(name, env);
}

void setValue(const char *name, Environ *env, Value value) {
    (*findValue(name, env)) = value;
}

#endif // ENVIRON_H_INCLUDED
