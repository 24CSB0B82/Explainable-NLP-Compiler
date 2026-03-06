#ifndef AST_H
#define AST_H

typedef enum {
    AST_PROGRAM,
    AST_BLOCK,
    AST_DECL_STMT,
    AST_DECLARATOR,
    AST_ASSIGN_STMT,
    AST_IF_STMT,
    AST_WHILE_STMT,
    AST_FUNC_CALL,
    AST_BINOP,
    AST_NUMBER,
    AST_IDENTIFIER,
    AST_STRING,
    AST_TYPE
} AstKind;

typedef struct AstNode {
    AstKind kind;
    char *text;
    int value;
    int line;
    struct AstNode *first_child;
    struct AstNode *next_sibling;
} AstNode;

AstNode *ast_create(AstKind kind, const char *text, int value, int line);
void ast_add_child(AstNode *parent, AstNode *child);
AstNode *ast_append_sibling(AstNode *head, AstNode *node);
void ast_print(const AstNode *node, int indent);
void ast_free(AstNode *node);

#endif
