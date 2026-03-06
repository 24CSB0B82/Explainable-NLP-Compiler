# Week 5 - Language and Grammar Design

## Restricted C-Subset (Supported Constructs)
- Types: `int`, `char`
- Declarations: single and comma-separated declarators
  - `int x;`
  - `int a = 5, b;`
- Assignment: `ID = expr;`
- Arithmetic expressions: `+`, `-`, `*`, `/`, parentheses
- Relational conditions: `>`, `<`, `>=`, `<=`, `==`, `!=`
- Control flow:
  - `if (condition) { ... }`
  - `if (condition) { ... } else { ... }`
  - `while (condition) { ... }`
- Function call statements: `ID(arg_list);`
- String literals as expression atoms

## Operator Precedence
1. `*`, `/`
2. `+`, `-`
3. Relational operators in condition context

## Grammar (EBNF-style)
```ebnf
program           := stmt_list_opt
stmt_list_opt     := stmt_list | epsilon
stmt_list         := stmt_list stmt | stmt
stmt              := declaration_stmt
                   | assignment_stmt
                   | if_stmt
                   | while_stmt
                   | function_call_stmt
                   | block

declaration_stmt  := type declarator_list ';'
type              := 'int' | 'char'
declarator_list   := declarator_list ',' declarator | declarator
declarator        := ID | ID '=' expr

assignment_stmt   := ID '=' expr ';'

expr              := expr '+' term
                   | expr '-' term
                   | term
term              := term '*' factor
                   | term '/' factor
                   | factor
factor            := NUMBER | ID | STRING | '(' expr ')'

if_stmt           := 'if' '(' condition ')' block
                   | 'if' '(' condition ')' block 'else' block
while_stmt        := 'while' '(' condition ')' block
condition         := expr relop expr | expr
relop             := '>' | '<' | '>=' | '<=' | '==' | '!='

block             := '{' stmt_list_opt '}'
function_call_stmt:= ID '(' arg_list ')' ';'
arg_list          := arg_list ',' expr | expr | epsilon
```

## Week-5 Sample Programs
- Valid samples: `test/valid/test1.c`, `test/valid/test2.c`, `test/valid/test3.c`
- Invalid samples: `test/invalid/test1_missing_semicolon.c`, `test/invalid/test2_bad_expr.c`, `test/invalid/test3_unclosed_block.c`
