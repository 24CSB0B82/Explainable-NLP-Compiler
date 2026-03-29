# Week 11 - Testing and Validation (Completed)

## Implementation Files
- `docs/week11_test_case_document.md`
- `test/scripts/week11_validate.sh`
- `Makefile`
- `test/week9`
- `test/week10`

## Validation Scope
Week 11 validates the behavior already implemented in weeks 9 and 10.

### Correctness Validation Inputs
- `test/week9/test_week9_use_before_initialization.c`
- `test/week9/test_week9_unreachable_code.c`
- `test/week9/test_week9_unused_variables.c`

### Security Validation Inputs
- `test/week10/test_week10_dangerous_calls.c`
- `test/week10/test_week10_hardcoded_password.c`
- `test/week10/test_week10_weak_rng.c`

### False-Positive Control
- `test/week10/test_week10_clean_control.c`

## Validation Rules
- Correctness cases must fail with exit code `1` and print the expected error category.
- Security warning cases must succeed with exit code `0` and print the expected warning category.
- The clean control case must succeed with exit code `0` and must not print any security warnings.

## Runner Behavior
- `test/scripts/week11_validate.sh` runs a focused validation matrix.
- Each case is checked for:
  - expected exit code
  - expected diagnostic pattern
  - optional absence of a diagnostic pattern
- The runner prints a final pass/fail summary and returns non-zero if any validation case fails.

## Build and Run
```bash
make build
make week11
```

## Expected Output Shape
- Individual `[PASS]` or `[FAIL]` lines per validation case
- A final summary line such as:
  - `Summary: 7 passed, 0 failed`

## Detection Accuracy
For the current week-11 validation matrix, detection accuracy is measured as:

`Accuracy = (number of correctly validated cases / total validation cases) * 100`

Current result on the implemented suite:
- Total validation cases: `7`
- Passed validation cases: `7`
- Detection accuracy on this suite: `100%`

This is validation accuracy for the current test matrix, not a benchmark against external datasets.

## Representative Fail Results
These are examples of what failure would look like if the implementation regressed.

### Example 1: Missed security warning
```text
[FAIL] Security: dangerous calls
  Expected exit: 0, actual exit: 0
  Expected pattern: dangerous function usage
```

### Example 2: False positive on clean control
```text
[FAIL] Validation: clean control has no security warnings
  Unexpected pattern found: Security warning
```

### Example 3: Wrong correctness exit code
```text
[FAIL] Correctness: unused variables
  Expected exit: 1, actual exit: 0
  Expected pattern: unused variable
```

## Validation Result Snapshot
- Correctness detection: validated for use-before-initialization, unreachable code, and unused variables
- Security detection: validated for dangerous functions, hard-coded credentials, and weak RNG
- False positives: validated with a clean control program that produces no security warnings

## False Positives and False Negatives
- False positive:
  - the compiler reports an issue when the input is actually acceptable
  - example: the clean control program gets a `Security warning`
- False negative:
  - the compiler misses an issue that should have been detected
  - example: `test_week10_weak_rng.c` runs without any weak-RNG warning

## What “Refine False Positives and Negatives” Means
- Improve rules when they are too broad and warn on safe code.
- Improve rules when they are too weak and miss unsafe or incorrect code.
- Add more targeted test cases after each rule change to confirm the improvement.
