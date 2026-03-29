# Week 12 - Performance Metrics

## Measurement Method
- Runner: `test/scripts/week12_compare.sh`
- Benchmark iterations: `5`
- Custom compiler command:
  - `./src/compiler --week10 test/week10/test_week10_mixed_warnings.c`
- GCC baseline command:
  - wrapped GCC-compatible version of `test/week10/test_week10_mixed_warnings.c`
  - `gcc -Wall -Wextra -std=gnu11 -O1 -fsyntax-only -Wuninitialized -Wmaybe-uninitialized`

## Current Results

| Tool | Average Time |
|---|---:|
| Custom compiler | `4 ms` |
| GCC baseline | `62 ms` |

## Notes
- These values are environment-specific and should be treated as local benchmark figures, not universal performance claims.
- The benchmark uses the same week-10 mixed-warning scenario for both tools.
- GCC is evaluated through a temporary wrapped translation unit so the restricted project input can be compared fairly.

## Interpretation
- On this local benchmark, the custom compiler completed faster than the GCC baseline for the selected case.
- The result is useful as a project-level snapshot, but broader benchmarking would require more inputs and repeated runs across environments.

## Reproduce
```bash
make build
make week12
```
