# Week 10 - Security Audit Rules (Completed)

## Implementation Files
- `src/security_audit.h`
- `src/security_audit.c`
- `src/parser.y`
- `src/lexer.l`
- `Makefile`

## Warning Semantics
- Week 10 findings are warnings, not errors.
- Warning-only programs keep exit code `0`.
- If syntax or correctness errors also exist, the compiler still returns non-zero.

## Implemented Warning Categories
- Hard-coded credentials
  - declaration or assignment to sensitive identifiers such as `password`, `passwd`, `secret`, `token`, `api_key`, `key`, `credential`
  - warning only when the assigned value is a literal `STRING` or `NUMBER`
- Dangerous function usage
  - `gets`, `strcpy`, `strcat`, `sprintf`, `scanf`
- Weak random number generation
  - any `rand()` call
  - `srand(...)` when the seed is a constant literal or constant expression

## Design Notes
- Security detection now lives in a dedicated AST-based audit pass.
- The lexer no longer emits security findings, so warnings are generated from a single source of truth.
- The security audit runs after correctness analysis and returns a warning count.

## Week-10 Test Inputs
- `test/week10/test_week10_hardcoded_password.c`
- `test/week10/test_week10_hardcoded_token_assignment.c`
- `test/week10/test_week10_dangerous_calls.c`
- `test/week10/test_week10_weak_rng.c`
- `test/week10/test_week10_mixed_warnings.c`
- `test/week10/test_week10_clean_control.c`

## Validation Expectations
- Hard-coded password and token files should print security warnings and still succeed.
- Dangerous function and weak RNG files should print security warnings and still succeed.
- Mixed warning file should print multiple warnings and still succeed.
- Clean control file should parse without week-10 warnings.

## Build and Run
```bash
make build
make week10
```
