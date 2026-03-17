# Test Layout

This project organizes tests by implementation week so the folder structure matches the project plan.

## Directories
- `test/week6` : lexical token-dump inputs for week 6
- `test/week7/valid` : valid syntax inputs for lexer/parser validation
- `test/week7/invalid` : invalid syntax inputs for parser recovery and syntax diagnostics
- `test/week8` : semantic checks introduced in week 8
- `test/week9` : correctness-analysis checks introduced in week 9
- `test/week10` : security warning checks introduced in week 10

## Make Targets
- `make week6` : runs the lexer-only token-dump driver
- `make week7` : runs week 7 syntax validation
- `make week8` : runs week 8 semantic-analysis tests
- `make week9` : runs week 9 correctness-analysis tests
- `make week10` : runs week 10 security warning tests
- `make test` : runs the full test suite
