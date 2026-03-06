#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

typedef struct Symbol {
    char *name;
    char *type;
    int declaration_line;
    int scope_level;
    struct Symbol *next;
} Symbol;

void symtab_init(void);
void symtab_enter_scope(void);
void symtab_exit_scope(void);
int symtab_declare(const char *name, const char *type, int line);
Symbol *symtab_lookup(const char *name);
void symtab_print(void);
void symtab_destroy(void);

#endif
