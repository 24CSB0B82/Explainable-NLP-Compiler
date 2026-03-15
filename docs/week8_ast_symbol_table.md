# Week 8 - AST Construction and Symbol Table (Completed)

## Implementation Files
- `src/ast.h`
- `src/ast.c`
- `src/symbol_table.h`
- `src/symbol_table.c`
- `src/parser.y` (integrated AST + symbol tracking)

## AST Design
### Node Model
Each AST node stores:
- `kind` (node category)
- `text` (identifier/operator/string/type where needed)
- `value` (numeric literal value)
- `line` (source line number)
- `first_child`, `next_sibling` (tree structure)

### Implemented Node Kinds
- `AST_PROGRAM`, `AST_BLOCK`
- `AST_DECL_STMT`, `AST_DECLARATOR`
- `AST_ASSIGN_STMT`, `AST_IF_STMT`, `AST_WHILE_STMT`, `AST_FUNC_CALL`
- `AST_BINOP`, `AST_NUMBER`, `AST_IDENTIFIER`, `AST_STRING`, `AST_TYPE`

### AST Utilities
- `ast_create`
- `ast_add_child`
- `ast_append_sibling`
- `ast_print`
- `ast_free`

## Symbol Table Design
### Scope Model
- Stack-based scopes (`Scope` linked list).
- Current block entry pushes scope.
- Block exit pops scope.

### Symbol Info
Each symbol stores:
- name
- type (`int` / `char`)
- declaration line
- scope level

### Implemented APIs
- `symtab_init`
- `symtab_enter_scope`
- `symtab_exit_scope`
- `symtab_declare`
- `symtab_lookup`
- `symtab_print`
- `symtab_destroy`

## Parser Integration (Week-8 Core)
- AST is constructed during parse actions in `parser.y`.
- Symbol declaration happens in declarator rules.
- Scope handling happens in block rule with enter/exit actions.
- Semantic checks integrated:
  - redeclaration detection in same scope
  - use-before-declaration detection

## Week-8 Semantic Validation
### Added tests
- `test/week7/valid/test4_scope_shadow.c` (scope shadowing valid case)
- `test/week8/test_week8_redeclaration.c` (redeclaration error)
- `test/week8/test_week8_use_before_declaration.c` (use-before-declaration error)

### Results
- `test4_scope_shadow.c` -> pass (exit `0`)
- `test_week8_redeclaration.c` -> semantic fail (exit `1`)
- `test_week8_use_before_declaration.c` -> semantic fail (exit `1`)

## Execution Behavior
On successful parse:
- prints `Parse successful`
- prints generated AST

On syntax/semantic issues:
- prints diagnostics with line numbers
- returns non-zero exit code
