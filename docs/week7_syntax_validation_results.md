# Week 7 - Syntax Analysis and Parsing (Completed)

## Implementation Files
- `src/parser.y`
- `src/lexer.l`

## Week-7 Functionality Delivered
- Bison parser for restricted C-subset grammar.
- Operator precedence and associativity:
  - `*`, `/` (higher)
  - `+`, `-` (lower)
  - relational operators in condition parsing
- Statement coverage:
  - declarations, assignments, arithmetic expressions
  - `if`, `if-else`, `while`, blocks, function-call statements
- Syntax error handling:
  - generic invalid statement recovery via `error ';'`
  - targeted missing semicolon recovery for assignment and function calls
- Line-aware syntax diagnostics using `yylineno`.
- Parser exit code policy:
  - `0` when syntax and semantic checks pass
  - `1` when any syntax/semantic issue is detected

## Syntax Validation Results
### Valid programs (`test/week7/valid`)
- `test1.c` -> pass (exit `0`)
- `test2.c` -> pass (exit `0`)
- `test3.c` -> pass (exit `0`)
- `test4_scope_shadow.c` -> pass (exit `0`)

### Invalid syntax programs (`test/week7/invalid`)
- `test1_missing_semicolon.c` -> fail (exit `1`), syntax recovery triggered
- `test2_bad_expr.c` -> fail (exit `1`), syntax recovery triggered
- `test3_unclosed_block.c` -> fail (exit `1`)

## Build and Run Commands
```bash
cd src
bison -d parser.y
flex lexer.l
gcc parser.tab.c lex.yy.c ast.c symbol_table.c correctness_analysis.c security_audit.c -o compiler -lfl

for f in ../test/week7/valid/*.c; do ./compiler "$f"; done
for f in ../test/week7/invalid/*.c; do ./compiler "$f"; done
```
