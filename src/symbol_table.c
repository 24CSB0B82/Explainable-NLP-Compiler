#include "symbol_table.h"
#include "explanation_engine.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Scope {
    int level;
    Symbol *symbols;
    struct Scope *next;
} Scope;

static Scope *scope_stack = NULL;

static char *sym_strdup(const char *s) {
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

void symtab_init(void) {
    scope_stack = NULL;
    symtab_enter_scope();
}

void symtab_enter_scope(void) {
    Scope *scope = (Scope *)malloc(sizeof(Scope));

    if (scope == NULL) {
        fprintf(stderr, "Symbol table error: cannot allocate scope\n");
        return;
    }

    scope->symbols = NULL;
    scope->next = scope_stack;
    if (scope_stack == NULL) {
        scope->level = 0;
    } else {
        scope->level = scope_stack->level + 1;
    }

    scope_stack = scope;
}

void symtab_exit_scope(void) {
    Symbol *symbol;
    Symbol *next_symbol;
    Scope *scope;

    if (scope_stack == NULL) {
        return;
    }

    scope = scope_stack;
    symbol = scope->symbols;
    while (symbol != NULL) {
        next_symbol = symbol->next;
        free(symbol->name);
        free(symbol->type);
        free(symbol);
        symbol = next_symbol;
    }

    scope_stack = scope->next;
    free(scope);
}

int symtab_declare(const char *name, const char *type, int line) {
    Symbol *cursor;
    Symbol *symbol;

    if (scope_stack == NULL) {
        symtab_init();
    }

    cursor = scope_stack->symbols;
    while (cursor != NULL) {
        if (strcmp(cursor->name, name) == 0) {
            fprintf(stderr,
                    "Semantic error (line %d): redeclaration of '%s' in scope %d\n",
                    line, name, scope_stack->level);
            explanation_emit(stderr, DIAG_SEVERITY_ERROR, DIAG_RULE_REDECLARATION, line, name);
            return 0;
        }
        cursor = cursor->next;
    }

    symbol = (Symbol *)malloc(sizeof(Symbol));
    if (symbol == NULL) {
        fprintf(stderr, "Symbol table error: cannot allocate symbol\n");
        return 0;
    }

    symbol->name = sym_strdup(name);
    symbol->type = sym_strdup(type);
    symbol->declaration_line = line;
    symbol->scope_level = scope_stack->level;
    symbol->next = scope_stack->symbols;
    scope_stack->symbols = symbol;

    return 1;
}

Symbol *symtab_lookup(const char *name) {
    Scope *scope = scope_stack;

    while (scope != NULL) {
        Symbol *symbol = scope->symbols;
        while (symbol != NULL) {
            if (strcmp(symbol->name, name) == 0) {
                return symbol;
            }
            symbol = symbol->next;
        }
        scope = scope->next;
    }

    return NULL;
}

void symtab_print(void) {
    Scope *scope = scope_stack;

    printf("\nSymbol Table Snapshot (top scope to bottom):\n");
    while (scope != NULL) {
        Symbol *symbol = scope->symbols;
        printf("Scope %d:\n", scope->level);
        if (symbol == NULL) {
            printf("  (empty)\n");
        }
        while (symbol != NULL) {
            printf("  %s : %s (declared at line %d)\n",
                   symbol->name,
                   symbol->type,
                   symbol->declaration_line);
            symbol = symbol->next;
        }
        scope = scope->next;
    }
}

void symtab_destroy(void) {
    while (scope_stack != NULL) {
        symtab_exit_scope();
    }
}
