#include "correctness_analysis.h"
#include "explanation_engine.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AnalysisSymbol {
    char *name;
    int declaration_line;
    int initialized;
    int used;
    struct AnalysisSymbol *next;
} AnalysisSymbol;

typedef struct AnalysisScope {
    AnalysisSymbol *symbols;
    struct AnalysisScope *next;
} AnalysisScope;

typedef struct {
    AnalysisScope *scope_stack;
    int error_count;
} AnalysisContext;

static char *analysis_strdup(const char *s) {
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

static void report_correctness_error(AnalysisContext *ctx, int line, const char *message, const char *name) {
    DiagnosticRule rule = DIAG_RULE_SYNTAX_GENERIC;

    if (!explanation_is_enabled()) {
        if (name != NULL) {
            fprintf(stderr, "Correctness error (line %d): %s '%s'\n", line, message, name);
        } else {
            fprintf(stderr, "Correctness error (line %d): %s\n", line, message);
        }
    }

    if (strcmp(message, "unused variable") == 0) {
        rule = DIAG_RULE_UNUSED_VARIABLE;
    } else if (strcmp(message, "use before initialization for") == 0) {
        rule = DIAG_RULE_USE_BEFORE_INITIALIZATION;
    } else if (strcmp(message, "unreachable statement") == 0) {
        rule = DIAG_RULE_UNREACHABLE_STATEMENT;
    }

    explanation_emit(stderr, DIAG_SEVERITY_ERROR, rule, line, name);
    ctx->error_count++;
}

static void push_scope(AnalysisContext *ctx) {
    AnalysisScope *scope = (AnalysisScope *)malloc(sizeof(AnalysisScope));

    if (scope == NULL) {
        return;
    }

    scope->symbols = NULL;
    scope->next = ctx->scope_stack;
    ctx->scope_stack = scope;
}

static void pop_scope(AnalysisContext *ctx) {
    AnalysisScope *scope;
    AnalysisSymbol *symbol;
    AnalysisSymbol *next_symbol;

    if (ctx->scope_stack == NULL) {
        return;
    }

    scope = ctx->scope_stack;
    symbol = scope->symbols;
    while (symbol != NULL) {
        next_symbol = symbol->next;
        if (!symbol->used) {
            report_correctness_error(ctx, symbol->declaration_line, "unused variable", symbol->name);
        }
        free(symbol->name);
        free(symbol);
        symbol = next_symbol;
    }

    ctx->scope_stack = scope->next;
    free(scope);
}

static AnalysisSymbol *find_symbol_in_scope(AnalysisScope *scope, const char *name) {
    AnalysisSymbol *symbol = scope != NULL ? scope->symbols : NULL;

    while (symbol != NULL) {
        if (strcmp(symbol->name, name) == 0) {
            return symbol;
        }
        symbol = symbol->next;
    }

    return NULL;
}

static AnalysisSymbol *lookup_symbol(AnalysisContext *ctx, const char *name) {
    AnalysisScope *scope = ctx->scope_stack;

    while (scope != NULL) {
        AnalysisSymbol *symbol = find_symbol_in_scope(scope, name);
        if (symbol != NULL) {
            return symbol;
        }
        scope = scope->next;
    }

    return NULL;
}

static void declare_symbol(AnalysisContext *ctx, const char *name, int line, int initialized) {
    AnalysisSymbol *symbol;

    if (ctx->scope_stack == NULL) {
        return;
    }

    if (find_symbol_in_scope(ctx->scope_stack, name) != NULL) {
        return;
    }

    symbol = (AnalysisSymbol *)malloc(sizeof(AnalysisSymbol));
    if (symbol == NULL) {
        return;
    }

    symbol->name = analysis_strdup(name);
    symbol->declaration_line = line;
    symbol->initialized = initialized;
    symbol->used = 0;
    symbol->next = ctx->scope_stack->symbols;
    ctx->scope_stack->symbols = symbol;
}

static void analyze_expr(AnalysisContext *ctx, const AstNode *expr);
static int analyze_stmt_list(AnalysisContext *ctx, const AstNode *stmt_list, int reachable);
static int eval_constant_expr(const AstNode *expr, int *value);

static void analyze_identifier_use(AnalysisContext *ctx, const AstNode *node) {
    AnalysisSymbol *symbol;

    if (node == NULL || node->text == NULL) {
        return;
    }

    symbol = lookup_symbol(ctx, node->text);
    if (symbol == NULL) {
        return;
    }

    symbol->used = 1;
    if (!symbol->initialized) {
        report_correctness_error(ctx, node->line, "use before initialization for", node->text);
    }
}

static void analyze_expr(AnalysisContext *ctx, const AstNode *expr) {
    const AstNode *child;

    if (expr == NULL) {
        return;
    }

    switch (expr->kind) {
        case AST_IDENTIFIER:
            analyze_identifier_use(ctx, expr);
            break;
        case AST_BINOP:
        case AST_FUNC_CALL:
            child = expr->first_child;
            while (child != NULL) {
                analyze_expr(ctx, child);
                child = child->next_sibling;
            }
            break;
        case AST_STRING:
        case AST_NUMBER:
        case AST_TYPE:
        case AST_PROGRAM:
        case AST_BLOCK:
        case AST_DECL_STMT:
        case AST_DECLARATOR:
        case AST_ASSIGN_STMT:
        case AST_IF_STMT:
        case AST_WHILE_STMT:
        default:
            child = expr->first_child;
            while (child != NULL) {
                analyze_expr(ctx, child);
                child = child->next_sibling;
            }
            break;
    }
}

static int eval_binop(const char *op, int left, int right, int *value) {
    if (strcmp(op, "+") == 0) {
        *value = left + right;
        return 1;
    }
    if (strcmp(op, "-") == 0) {
        *value = left - right;
        return 1;
    }
    if (strcmp(op, "*") == 0) {
        *value = left * right;
        return 1;
    }
    if (strcmp(op, "/") == 0) {
        if (right == 0) {
            return 0;
        }
        *value = left / right;
        return 1;
    }
    if (strcmp(op, ">") == 0) {
        *value = left > right;
        return 1;
    }
    if (strcmp(op, "<") == 0) {
        *value = left < right;
        return 1;
    }
    if (strcmp(op, ">=") == 0) {
        *value = left >= right;
        return 1;
    }
    if (strcmp(op, "<=") == 0) {
        *value = left <= right;
        return 1;
    }
    if (strcmp(op, "==") == 0) {
        *value = left == right;
        return 1;
    }
    if (strcmp(op, "!=") == 0) {
        *value = left != right;
        return 1;
    }
    return 0;
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

    return eval_binop(expr->text, left, right, value);
}

static void clone_scope_flags(AnalysisScope *dst, AnalysisScope *src) {
    AnalysisSymbol *dst_symbol;

    while (dst != NULL && src != NULL) {
        dst_symbol = dst->symbols;
        while (dst_symbol != NULL) {
            AnalysisSymbol *src_symbol = find_symbol_in_scope(src, dst_symbol->name);
            if (src_symbol != NULL) {
                dst_symbol->initialized = src_symbol->initialized;
                dst_symbol->used = src_symbol->used;
            }
            dst_symbol = dst_symbol->next;
        }
        dst = dst->next;
        src = src->next;
    }
}

static AnalysisScope *clone_scope_stack(AnalysisScope *scope) {
    AnalysisScope *new_head = NULL;
    AnalysisScope *new_tail = NULL;

    while (scope != NULL) {
        AnalysisScope *scope_copy = (AnalysisScope *)malloc(sizeof(AnalysisScope));
        AnalysisSymbol *src_symbol = scope->symbols;
        AnalysisSymbol *dst_tail = NULL;

        if (scope_copy == NULL) {
            return new_head;
        }

        scope_copy->symbols = NULL;
        scope_copy->next = NULL;

        while (src_symbol != NULL) {
            AnalysisSymbol *symbol_copy = (AnalysisSymbol *)malloc(sizeof(AnalysisSymbol));
            if (symbol_copy == NULL) {
                src_symbol = src_symbol->next;
                continue;
            }

            symbol_copy->name = analysis_strdup(src_symbol->name);
            symbol_copy->declaration_line = src_symbol->declaration_line;
            symbol_copy->initialized = src_symbol->initialized;
            symbol_copy->used = src_symbol->used;
            symbol_copy->next = NULL;

            if (scope_copy->symbols == NULL) {
                scope_copy->symbols = symbol_copy;
            } else {
                dst_tail->next = symbol_copy;
            }
            dst_tail = symbol_copy;
            src_symbol = src_symbol->next;
        }

        if (new_head == NULL) {
            new_head = scope_copy;
        } else {
            new_tail->next = scope_copy;
        }
        new_tail = scope_copy;
        scope = scope->next;
    }

    return new_head;
}

static void free_scope_stack(AnalysisScope *scope) {
    while (scope != NULL) {
        AnalysisScope *next_scope = scope->next;
        AnalysisSymbol *symbol = scope->symbols;

        while (symbol != NULL) {
            AnalysisSymbol *next_symbol = symbol->next;
            free(symbol->name);
            free(symbol);
            symbol = next_symbol;
        }

        free(scope);
        scope = next_scope;
    }
}

static int analyze_stmt(AnalysisContext *ctx, const AstNode *stmt, int reachable) {
    const AstNode *child;
    AnalysisSymbol *symbol;
    int const_value;
    int then_reachable;
    AnalysisScope *before_if;
    AnalysisScope *then_state;
    AnalysisScope *else_state;

    if (stmt == NULL) {
        return reachable;
    }

    if (!reachable) {
        report_correctness_error(ctx, stmt->line, "unreachable statement", NULL);
        return 0;
    }

    switch (stmt->kind) {
        case AST_DECL_STMT:
            child = stmt->first_child;
            if (child != NULL) {
                child = child->next_sibling;
            }
            while (child != NULL) {
                declare_symbol(ctx, child->text, child->line, child->first_child != NULL);
                if (child->first_child != NULL) {
                    analyze_expr(ctx, child->first_child);
                }
                child = child->next_sibling;
            }
            return 1;
        case AST_ASSIGN_STMT:
            analyze_expr(ctx, stmt->first_child);
            symbol = lookup_symbol(ctx, stmt->text);
            if (symbol != NULL) {
                symbol->initialized = 1;
            }
            return 1;
        case AST_FUNC_CALL:
            child = stmt->first_child;
            while (child != NULL) {
                analyze_expr(ctx, child);
                child = child->next_sibling;
            }
            return 1;
        case AST_BLOCK:
            push_scope(ctx);
            (void)analyze_stmt_list(ctx, stmt->first_child, 1);
            pop_scope(ctx);
            return 1;
        case AST_IF_STMT:
            child = stmt->first_child;
            analyze_expr(ctx, child);
            then_reachable = eval_constant_expr(child, &const_value);
            before_if = clone_scope_stack(ctx->scope_stack);

            child = child != NULL ? child->next_sibling : NULL;
            if (then_reachable && const_value == 0 && child != NULL) {
                report_correctness_error(ctx, child->line, "unreachable statement", NULL);
            } else if (child != NULL) {
                (void)analyze_stmt(ctx, child, 1);
            }
            then_state = clone_scope_stack(ctx->scope_stack);

            if (before_if != NULL) {
                free_scope_stack(ctx->scope_stack);
                ctx->scope_stack = clone_scope_stack(before_if);
            }

            child = child != NULL ? child->next_sibling : NULL;
            if (child != NULL) {
                if (then_reachable && const_value != 0) {
                    report_correctness_error(ctx, child->line, "unreachable statement", NULL);
                } else {
                    (void)analyze_stmt(ctx, child, 1);
                }
                else_state = clone_scope_stack(ctx->scope_stack);
            } else {
                else_state = clone_scope_stack(before_if);
            }

            if (before_if != NULL) {
                clone_scope_flags(before_if, then_state != NULL ? then_state : before_if);
                if (else_state != NULL) {
                    AnalysisScope *merged_scope = before_if;
                    AnalysisScope *then_scope = then_state;
                    AnalysisScope *cur_else_scope = else_state;

                    while (merged_scope != NULL && then_scope != NULL && cur_else_scope != NULL) {
                        AnalysisSymbol *merged_symbol = merged_scope->symbols;

                        while (merged_symbol != NULL) {
                            AnalysisSymbol *then_symbol = find_symbol_in_scope(then_scope, merged_symbol->name);
                            AnalysisSymbol *else_symbol = find_symbol_in_scope(cur_else_scope, merged_symbol->name);
                            if (then_symbol != NULL && else_symbol != NULL) {
                                merged_symbol->initialized = then_symbol->initialized && else_symbol->initialized;
                                merged_symbol->used = then_symbol->used || else_symbol->used;
                            }
                            merged_symbol = merged_symbol->next;
                        }

                        merged_scope = merged_scope->next;
                        then_scope = then_scope->next;
                        cur_else_scope = cur_else_scope->next;
                    }
                }

                free_scope_stack(ctx->scope_stack);
                ctx->scope_stack = before_if;
            }

            free_scope_stack(then_state);
            free_scope_stack(else_state);
            return 1;
        case AST_WHILE_STMT:
            child = stmt->first_child;
            analyze_expr(ctx, child);
            if (eval_constant_expr(child, &const_value)) {
                const AstNode *body = child != NULL ? child->next_sibling : NULL;
                if (const_value == 0) {
                    if (body != NULL) {
                        report_correctness_error(ctx, body->line, "unreachable statement", NULL);
                    }
                    return 1;
                }
                if (body != NULL) {
                    (void)analyze_stmt(ctx, body, 1);
                }
                return 0;
            }

            child = child != NULL ? child->next_sibling : NULL;
            if (child != NULL) {
                AnalysisScope *before_loop = clone_scope_stack(ctx->scope_stack);
                (void)analyze_stmt(ctx, child, 1);
                free_scope_stack(ctx->scope_stack);
                ctx->scope_stack = before_loop;
            }
            return 1;
        default:
            return 1;
    }
}

static int analyze_stmt_list(AnalysisContext *ctx, const AstNode *stmt_list, int reachable) {
    const AstNode *stmt = stmt_list;
    int current_reachable = reachable;

    while (stmt != NULL) {
        current_reachable = analyze_stmt(ctx, stmt, current_reachable);
        stmt = stmt->next_sibling;
    }

    return current_reachable;
}

int run_correctness_analysis(const AstNode *root) {
    AnalysisContext ctx;

    ctx.scope_stack = NULL;
    ctx.error_count = 0;

    push_scope(&ctx);
    if (root != NULL) {
        analyze_stmt_list(&ctx, root->first_child, 1);
    }
    pop_scope(&ctx);

    return ctx.error_count;
}
