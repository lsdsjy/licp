#include <stdio.h>
#include "environ.h"
#include "eval.h"

Environ *globalEnv() {
    Environ *env = newEnviron(NULL);
    return env;
}

int main() {
    char exp[1024];
    Node *root;
    Environ *env = globalEnv();
    while (fgets(exp, 1024, stdin)) {
        root = newNode(NULL, NULL, NULL);
        parse(exp, root);
        //printTree(root, 1);
        printf("%d\n", eval(root, env).num);
    }
    return 0;
}
