#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "block.h"

typedef struct _Node {
    char *exp;
    struct _Node *next;
    struct _Node *child;
} Node;

Node *newNode(Node *prev, Node *parent, const char *exp) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->next = node->child = NULL;
    if (exp) {
        node->exp = (char *)malloc(strlen(exp) + 1);
        strcpy(node->exp, exp);
    } else {
        node->exp = NULL;
    }

    if (prev) {
        prev->next = node;
    } else {
        if (parent) {
            parent->child = node;
        }
    }

    return node;
}

void printTree(Node *node, int depth) {
    if (node == NULL) {
        return;
    }
    printf("%d %s\n", depth, node->exp ? node->exp : "(...)");
    printTree(node->child, depth + 1);
    printTree(node->next, depth);
}

#endif // NODE_H_INCLUDED
