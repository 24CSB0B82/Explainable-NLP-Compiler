# Week 9 - Correctness Analysis (Completed)

## Implementation Files
- `src/correctness_analysis.h`
- `src/correctness_analysis.c`
- `src/parser.y`
- `Makefile`

## Week-9 Functionality Delivered
- Dedicated correctness-analysis pass over the AST after successful parsing.
- Compile-time error detection for:
  - use-before-initialization
  - unreachable code
  - unused variables
- Line-aware diagnostics through a centralized reporting path.
- Non-zero process exit when correctness errors are detected.

## Analysis Design
- The module walks the AST built in week 8 instead of mixing all logic into parser actions.
- A separate analysis scope stack tracks variable state:
  - declared
  - initialized
  - used
- Block scopes are handled independently, matching the parser's block structure.

## Implemented Rules
### 1. Use Before Initialization
- A variable declared without an initializer is marked uninitialized.
- Identifier reads in expressions and conditions are validated before use.
- Assignment marks the left-hand side variable as initialized after the right-hand side is analyzed.

### 2. Unreachable Code
- `if (0) { ... }` marks the `then` block as unreachable.
- `if (constant_nonzero) ... else ...` marks the `else` block as unreachable.
- `while (0) { ... }` marks the loop body as unreachable.
- `while (constant_nonzero) { ... }` marks following statements as unreachable in this restricted language subset.

### 3. Unused Variables
- Variables not read before scope exit are reported as unused.
- Scope-local variables are checked when their scope closes.

## Week-9 Test Inputs
- `test/week9/test_week9_use_before_initialization.c`
- `test/week9/test_week9_unreachable_code.c`
- `test/week9/test_week9_unused_variables.c`

## Validation Summary
- `test_week9_use_before_initialization.c` -> detects uninitialized read
- `test_week9_unreachable_code.c` -> detects unreachable branches/statements
- `test_week9_unused_variables.c` -> detects unused variables across nested scopes

## Build and Run
```bash
make build
make week9
```

Week 9 runs the compiler in `--week9` mode so correctness analysis is enabled while the week-10 security audit remains disabled.
