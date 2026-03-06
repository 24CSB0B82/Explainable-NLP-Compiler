#include "ast.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *ast_strdup(const char *s) {
    size_t n;
    char *copy;

    if (s == NULL) {
        return NULL;
    }

    n = strlen(s);
    copy = (char *)malloc(n + 1);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, s, n + 1);
    return copy;
}

static const char *ast_kind_name(AstKind kind) {
    switch (kind) {
        case AST_PROGRAM: return "PROGRAM";
        case AST_BLOCK: return "BLOCK";
        case AST_DECL_STMT: return "DECL_STMT";
        case AST_DECLARATOR: return "DECLARATOR";
        case AST_ASSIGN_STMT: return "ASSIGN_STMT";
        case AST_IF_STMT: return "IF_STMT";
        case AST_WHILE_STMT: return "WHILE_STMT";
        case AST_FUNC_CALL: return "FUNC_CALL";
        case AST_BINOP: return "BINOP";
        case AST_NUMBER: return "NUMBER";
        case AST_IDENTIFIER: return "IDENTIFIER";
        case AST_STRING: return "STRING";
        case AST_TYPE: return "TYPE";
        default: return "UNKNOWN";
    }
}

AstNode *ast_create(AstKind kind, const char *text, int value, int line) {
    AstNode *node = (AstNode *)malloc(sizeof(AstNode));

    if (node == NULL) {
        return NULL;
    }

    node->kind = kind;
    node->text = ast_strdup(text);
    node->value = value;
    node->line = line;
    node->first_child = NULL;
    node->next_sibling = NULL;

    return node;
}

void ast_add_child(AstNode *parent, AstNode *child) {
    AstNode *tail;

    if (parent == NULL || child == NULL) {
        return;
    }

    if (parent->first_child == NULL) {
        parent->first_child = child;
        return;
    }

    tail = parent->first_child;
    while (tail->next_sibling != NULL) {
        tail = tail->next_sibling;
    }

    tail->next_sibling = child;
}

AstNode *ast_append_sibling(AstNode *head, AstNode *node) {
    AstNode *tail;

    if (head == NULL) {
        return node;
    }

    if (node == NULL) {
        return head;
    }

    tail = head;
    while (tail->next_sibling != NULL) {
        tail = tail->next_sibling;
    }

    tail->next_sibling = node;
    return head;
}

void ast_print(const AstNode *node, int indent) {
    int i;
    const AstNode *cursor = node;

    while (cursor != NULL) {
        for (i = 0; i < indent; i++) {
            putchar(' ');
        }

        printf("%s", ast_kind_name(cursor->kind));
        if (cursor->text != NULL) {
            printf("(%s)", cursor->text);
        } else if (cursor->kind == AST_NUMBER) {
            printf("(%d)", cursor->value);
        }
        printf(" [line %d]\n", cursor->line);

        if (cursor->first_child != NULL) {
            ast_print(cursor->first_child, indent + 2);
        }

        cursor = cursor->next_sibling;
    }
}

void ast_free(AstNode *node) {
    AstNode *next;

    while (node != NULL) {
        next = node->next_sibling;
        ast_free(node->first_child);
        free(node->text);
        free(node);
        node = next;
    }
}
