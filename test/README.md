# Test Layout

This project organizes tests by implementation week so the folder structure matches the project plan.

## Directories
- `test/week6` : lexical token-dump inputs for week 6
- `test/week7/valid` : valid syntax inputs for lexer/parser validation
- `test/week7/invalid` : invalid syntax inputs for parser recovery and syntax diagnostics
- `test/week8` : semantic checks introduced in week 8
- `test/week9` : correctness-analysis checks introduced in week 9
- `test/week10` : security warning checks introduced in week 10
- `test/scripts/week11_validate.sh` : week 11 validation runner over correctness and security suites
- `test/week12/case_matrix.tsv` : week 12 comparison matrix for custom compiler vs GCC
- `test/scripts/week12_compare.sh` : week 12 comparative evaluation and performance runner
- `test/week13` : explanation samples for syntax, correctness, and security findings
- `test/scripts/week13_explain.sh` : week 13 explanation runner

## Make Targets
- `make week6` : runs the lexer-only token-dump driver
- `make week7` : runs week 7 syntax validation
- `make week8` : runs week 8 semantic-analysis tests
- `make week9` : runs week 9 correctness-analysis tests
- `make week10` : runs week 10 security warning tests
- `make week11` : runs validation checks and prints a pass/fail summary
- `make week12` : runs comparative evaluation and performance metrics
- `make week13` : runs sample NLP-style explanations
- `make test` : runs the full test suite
