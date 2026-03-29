# Week 11 - Test Case Document

## What a Test Case Document Should Include
- Test case ID
- Objective
- Input file path
- Analysis mode used
- Expected exit code
- Expected output category
- Actual result
- Status (`PASS` / `FAIL`)

## Current Week-11 Test Matrix

| Test Case ID | Objective | Input File | Mode | Expected Exit | Expected Result |
|---|---|---|---|---:|---|
| W11-COR-01 | Detect use-before-initialization | `test/week9/test_week9_use_before_initialization.c` | `--week9` | 1 | `Correctness error` for uninitialized use |
| W11-COR-02 | Detect unreachable code | `test/week9/test_week9_unreachable_code.c` | `--week9` | 1 | `Correctness error` for unreachable statement |
| W11-COR-03 | Detect unused variables | `test/week9/test_week9_unused_variables.c` | `--week9` | 1 | `Correctness error` for unused variable |
| W11-SEC-01 | Detect dangerous functions | `test/week10/test_week10_dangerous_calls.c` | `--week10` | 0 | `Security warning` for dangerous function usage |
| W11-SEC-02 | Detect hard-coded credentials | `test/week10/test_week10_hardcoded_password.c` | `--week10` | 0 | `Security warning` for hard-coded credential |
| W11-SEC-03 | Detect weak RNG | `test/week10/test_week10_weak_rng.c` | `--week10` | 0 | `Security warning` for weak random number generation |
| W11-CTL-01 | Check false-positive control | `test/week10/test_week10_clean_control.c` | `--week10` | 0 | `Parse successful` with no security warning |

## How to Extend It
- Add more correctness cases under `test/week9`
- Add more security cases under `test/week10`
- Add more clean controls to verify false positives remain low
- Re-run `make week11` after adding cases so the validation matrix stays current
