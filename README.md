# Explainable NLP Compiler for Security Audits

This project implements a restricted C compiler front-end with explainable diagnostics. It detects syntax, semantic, correctness, and security issues, then converts those findings into readable NLP-style explanations with suggested fixes.

## Project Goal
- build a restricted C compiler using Flex and Bison
- detect correctness and security issues at compile time
- generate human-readable explanations for detected issues
- keep the project organized by weekly execution-plan phases

## Final Pipeline
```text
Source Program
    |
    v
Lexer (Flex)
    |
    v
Parser (Bison)
    |
    v
   AST
    |
    v
Symbol Table / Semantic Checks
    |
    v
Correctness Analysis
    |
    v
Security Audit
    |
    v
NLP Explanation Engine
```

## Core Features
- lexical analysis for restricted C tokens
- syntax analysis with recovery for malformed inputs
- AST construction for parsed programs
- symbol table with scope-aware declaration checks
- correctness analysis:
  - use before initialization
  - unreachable statements
  - unused variables
- security audit:
  - hard-coded credentials
  - dangerous function usage
  - weak RNG and predictable seeding
- rule-based explanation engine with:
  - `Error:` or `Warning:`
  - `Type:`
  - `Explanation:`
  - `Fix:`

## Project Structure
- `src/` : compiler source files
- `docs/` : weekly reports and final documentation
- `test/` : week-based test inputs, matrices, and scripts
- `Makefile` : build and test automation

## Main Files
- `src/lexer.l`
- `src/parser.y`
- `src/ast.c`
- `src/ast.h`
- `src/symbol_table.c`
- `src/symbol_table.h`
- `src/correctness_analysis.c`
- `src/correctness_analysis.h`
- `src/security_audit.c`
- `src/security_audit.h`
- `src/explanation_engine.c`
- `src/explanation_engine.h`

## Build Requirements
- `gcc`
- `flex`
- `bison`
- `make`

## Build
```bash
make build
```

## Run
Week-based usage examples:

```bash
make week6
make week10
make week14
```

Direct compiler usage:

```bash
./src/compiler test/week7/valid/test1.c
./src/compiler --week10 test/week10/test_week10_dangerous_calls.c
./src/compiler --week14 test/week9/test_week9_use_before_initialization.c
```

## Final Output Style
```text
Error: Variable is used before initialization. Subject: 'value'. Line: 4.
Type: Correctness Error
Explanation: The variable is read before the program assigns any value to it on the reachable path.
Fix: Initialize the variable at declaration time or assign to it before using it.
```

## Make Targets
- `make week6` : lexer token-dump validation
- `make week7` : syntax validation
- `make week8` : semantic validation
- `make week9` : correctness validation
- `make week10` : security validation
- `make week11` : testing and validation summary
- `make week12` : comparison and benchmarking
- `make week13` : explanation samples
- `make week14` : final integrated NLP validation
- `make test` : full project test suite

## Documentation
- `docs/week14_final_integration_report.md`
- `docs/final_project_report.md`
- `test/README.md`

## Author
Sai Jaswanth
