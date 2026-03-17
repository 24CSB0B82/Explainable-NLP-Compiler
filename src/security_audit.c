#include "security_audit.h"

#include <stdio.h>
#include <string.h>

typedef struct {
    int warning_count;
} SecurityAuditContext;

static void report_security_warning(SecurityAuditContext *ctx, int line, const char *message, const char *name) {
    if (name != NULL) {
        fprintf(stderr, "Security warning (line %d): %s '%s'\n", line, message, name);
    } else {
        fprintf(stderr, "Security warning (line %d): %s\n", line, message);
    }
    ctx->warning_count++;
}

static int is_sensitive_identifier(const char *name) {
    static const char *sensitive_names[] = {
        "password", "passwd", "secret", "token", "api_key", "key", "credential"
    };
    int i;

    if (name == NULL) {
        return 0;
    }

    for (i = 0; i < (int)(sizeof(sensitive_names) / sizeof(sensitive_names[0])); i++) {
        if (strcmp(name, sensitive_names[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

static int is_dangerous_function(const char *name) {
    static const char *dangerous_functions[] = {
        "gets", "strcpy", "strcat", "sprintf", "scanf"
    };
    int i;

    if (name == NULL) {
        return 0;
    }

    for (i = 0; i < (int)(sizeof(dangerous_functions) / sizeof(dangerous_functions[0])); i++) {
        if (strcmp(name, dangerous_functions[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

static int is_literal_secret_value(const AstNode *node) {
    if (node == NULL) {
        return 0;
    }

    return node->kind == AST_STRING || node->kind == AST_NUMBER;
}

static int eval_constant_expr(const AstNode *expr, int *value) {
    int left;
    int right;
    const AstNode *lhs;
    const AstNode *rhs;

    if (expr == NULL) {
        return 0;
    }

    if (expr->kind == AST_NUMBER) {
        *value = expr->value;
        return 1;
    }

    if (expr->kind != AST_BINOP || expr->text == NULL) {
        return 0;
    }

    lhs = expr->first_child;
    rhs = lhs != NULL ? lhs->next_sibling : NULL;
    if (lhs == NULL || rhs == NULL) {
        return 0;
    }

    if (!eval_constant_expr(lhs, &left) || !eval_constant_expr(rhs, &right)) {
        return 0;
    }

    if (strcmp(expr->text, "+") == 0) {
        *value = left + right;
        return 1;
    }
    if (strcmp(expr->text, "-") == 0) {
        *value = left - right;
        return 1;
    }
    if (strcmp(expr->text, "*") == 0) {
        *value = left * right;
        return 1;
    }
    if (strcmp(expr->text, "/") == 0 && right != 0) {
        *value = left / right;
        return 1;
    }

    return 0;
}

static void audit_node(SecurityAuditContext *ctx, const AstNode *node) {
    const AstNode *child;

    if (node == NULL) {
        return;
    }

    switch (node->kind) {
        case AST_DECLARATOR:
            if (is_sensitive_identifier(node->text) && is_literal_secret_value(node->first_child)) {
                report_security_warning(ctx, node->line, "hard-coded credential assigned to", node->text);
            }
            break;
        case AST_ASSIGN_STMT:
            if (is_sensitive_identifier(node->text) && is_literal_secret_value(node->first_child)) {
                report_security_warning(ctx, node->line, "hard-coded credential assigned to", node->text);
            }
            break;
        case AST_FUNC_CALL:
            if (is_dangerous_function(node->text)) {
                report_security_warning(ctx, node->line, "dangerous function usage", node->text);
            }
            if (node->text != NULL && strcmp(node->text, "rand") == 0) {
                report_security_warning(ctx, node->line, "weak random number generation using", node->text);
            }
            if (node->text != NULL && strcmp(node->text, "srand") == 0) {
                int seed_value = 0;
                if (eval_constant_expr(node->first_child, &seed_value)) {
                    report_security_warning(ctx, node->line, "predictable random seed in", node->text);
                }
            }
            break;
        default:
            break;
    }

    child = node->first_child;
    while (child != NULL) {
        audit_node(ctx, child);
        child = child->next_sibling;
    }
}

int run_security_audit(const AstNode *root) {
    SecurityAuditContext ctx;

    ctx.warning_count = 0;
    if (root != NULL) {
        audit_node(&ctx, root);
    }

    return ctx.warning_count;
}
