# Week 13 - Explainability and Interpretability

## Goal
Week 13 adds a rule-based NLP explanation layer on top of the existing compiler diagnostics.

The compiler already knows how to detect:
- syntax errors
- semantic errors
- correctness-analysis errors
- security warnings

Week 13 makes those findings easier to understand by turning them into:
- a technical diagnostic
- a typed issue category
- a human-readable explanation
- a suggested fix
- a location reference

## Design Approach
The explanation layer is implemented as a dedicated module:
- `src/explanation_engine.h`
- `src/explanation_engine.c`

This keeps the architecture clean:
- analysis modules decide **what is wrong**
- the explanation engine decides **how to explain it**

## Why Rule-Based NLP
This project uses rule-based NLP instead of machine learning because:
- the compiler findings are already rule-driven
- outputs must stay predictable and explainable
- each issue type maps naturally to a reusable explanation template
- it is easier to validate in an academic compiler project

## Explanation Format
For each supported issue, the compiler can print:
- original diagnostic
- `Type: ...`
- `Explanation: ...`
- `Fix: ...`
- `Location: ...`

Example structure:
```text
Correctness error (line 4): use before initialization for 'value'
Type: Correctness Error (value)
Explanation: The variable is read before the program assigns any value to it on the reachable path.
Fix: Initialize the variable at declaration time or assign to it before using it.
Location: line 4
```

## Supported Explanation Categories
- Syntax
  - generic syntax mismatch
  - missing semicolon
- Semantic / Symbol Table
  - undeclared identifier
  - redeclaration
- Correctness Analysis
  - use-before-initialization
  - unreachable statement
  - unused variable
- Security Audit
  - hard-coded credential
  - dangerous function usage
  - weak random number generation
  - predictable random seed

## Execution Mode
Week 13 uses a dedicated compiler mode:
```bash
./src/compiler --week13 <input-file>
```

The `--week13` mode:
- runs correctness analysis
- runs security audit
- enables the explanation engine

## Implementation Files
- `src/explanation_engine.h`
- `src/explanation_engine.c`
- `src/parser.y`
- `src/correctness_analysis.c`
- `src/security_audit.c`
- `src/symbol_table.c`
- `test/scripts/week13_explain.sh`
- `test/week13`
