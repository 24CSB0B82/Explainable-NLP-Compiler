# Explainable NLP Compiler for Security Audits

This project implements a **restricted C compiler with explainable diagnostics** to detect correctness errors and security issues in programs.

The compiler provides human-readable explanations for detected problems, improving the usability of static analysis tools.

It stands between: 
1. Static Analysis
2. Semantic Analysis
3. Explainability using NLP

---

## Project Architecture

The compiler follows a standard front-end pipeline:

Source Code
    ↓
Lexical Analysis (Flex)
    ↓
Syntax Analysis (Bison)
    ↓
AST Construction
    ↓
Symbol Table
    ↓
Correctness Analysis
    ↓
Explainable Diagnostics

---

## Project Structure
Explainable-NLP-Compiler
│
├── docs → Weekly reports and documentation
├── src → Compiler source code
├── test → Test programs
├── Makefile → Build automation
└── .gitignore

---

## Modules

### Lexical Analysis
Implemented using **Flex**.

File: src/lexer.l

Responsible for:
- Tokenization
- Keyword recognition
- Identifier detection

---

### Syntax Analysis

Implemented using **Bison**.

File: src/parser.y

Handles:

- Grammar validation
- Operator precedence
- Syntax error detection

---

### AST Construction

Files: src/ast.c, src/ast.h

Creates the **Abstract Syntax Tree** used by later analysis phases.

---

### Symbol Table

Files: src/symbol_table.c, src/symbol_table.h

Tracks:

- Variables
- Scope
- Declarations

---

### Correctness Analysis

Files: src/correctness_analysis.c, src/correctness_analysis.h

Detects:

- Use-before-initialization
- Unused variables
- Unreachable code

---

## Build Instructions

Requirements:

- GCC
- Flex
- Bison
- Make

Compile: make

---

## Run the Compiler

Example: ./compiler test/week7/valid/test1.c

---

## Sample Output
ERROR: Variable 'x' used before initialization.
WARNING: Unreachable code detected.

---

## Future Work

- Security audit rule detection
- NLP-based explanation engine
- Integration with static analysis tools

---

## Author

Sai Jaswanth
B.Tech Computer Science
