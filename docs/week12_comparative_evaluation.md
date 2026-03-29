# Week 12 - Comparative Evaluation Report

## Implementation Files
- `test/scripts/week12_compare.sh`
- `test/week12/case_matrix.tsv`
- `Makefile`

## Comparison Baseline
- Custom compiler:
  - `src/compiler`
- Traditional compiler baseline:
  - `gcc`
  - flags: `-Wall -Wextra -std=gnu11 -O1 -fsyntax-only -Wuninitialized -Wmaybe-uninitialized`

## Evaluation Matrix

| Case ID | Category | Input File | Our Compiler | GCC | Observation |
|---|---|---|---|---|---|
| W12-SYN-01 | Syntax | `test/week7/invalid/test2_bad_expr.c` | syntax diagnostic | gcc error | both catch syntax issue |
| W12-COR-01 | Correctness | `test/week9/test_week9_use_before_initialization.c` | correctness diagnostic | no diagnostic | custom only |
| W12-COR-02 | Correctness | `test/week9/test_week9_unreachable_code.c` | correctness diagnostic | no diagnostic | custom only |
| W12-SEC-01 | Security | `test/week10/test_week10_hardcoded_password.c` | security warning | no diagnostic | custom security only |
| W12-SEC-02 | Security | `test/week10/test_week10_dangerous_calls.c` | security warning | gcc warning | custom security, gcc generic |
| W12-SEC-03 | Security | `test/week10/test_week10_weak_rng.c` | security warning | no diagnostic | custom security only |
| W12-CTL-01 | Control | `test/week10/test_week10_clean_control.c` | clean success | no diagnostic | both accept |

## Key Findings
- Syntax checking overlaps with GCC for malformed input.
- Week-9 correctness rules provide additional diagnostics not produced by GCC on the current matrix.
- Week-10 security rules provide domain-specific security warnings that GCC generally does not produce.
- Dangerous function usage is the only current case where GCC also emits a generic warning, but it is not a security-classified explanation.

## Interpretation
- The custom compiler adds value beyond traditional compiler diagnostics for correctness-analysis and security-audit tasks.
- GCC remains a useful syntax baseline, but it does not replace project-specific correctness and security rules.

## Reproduce
```bash
make build
make week12
```
