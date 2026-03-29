#!/usr/bin/env bash
set -u

ROOT_DIR="$(cd "$(dirname "$0")/../.." && pwd)"
COMPILER="$ROOT_DIR/src/compiler"

pass_count=0
fail_count=0

run_case() {
    local label="$1"
    local mode="$2"
    local file="$3"
    local expected_exit="$4"
    local expected_pattern="$5"
    local unexpected_pattern="${6:-}"
    local stdout_file
    local stderr_file
    local exit_code

    stdout_file="$(mktemp)"
    stderr_file="$(mktemp)"

    if [ "$mode" = "-" ]; then
        "$COMPILER" "$file" >"$stdout_file" 2>"$stderr_file"
    else
        "$COMPILER" "$mode" "$file" >"$stdout_file" 2>"$stderr_file"
    fi
    exit_code=$?

    if [ "$exit_code" -eq "$expected_exit" ] && grep -q "$expected_pattern" "$stderr_file" "$stdout_file"; then
        if [ -n "$unexpected_pattern" ] && grep -q "$unexpected_pattern" "$stderr_file" "$stdout_file"; then
            echo "[FAIL] $label"
            echo "  Unexpected pattern found: $unexpected_pattern"
            fail_count=$((fail_count + 1))
        else
            echo "[PASS] $label"
            pass_count=$((pass_count + 1))
        fi
    else
        echo "[FAIL] $label"
        echo "  Expected exit: $expected_exit, actual exit: $exit_code"
        echo "  Expected pattern: $expected_pattern"
        echo "  stdout:"
        sed -n '1,40p' "$stdout_file"
        echo "  stderr:"
        sed -n '1,40p' "$stderr_file"
        fail_count=$((fail_count + 1))
    fi

    rm -f "$stdout_file" "$stderr_file"
}

echo "Week 11 validation run"
echo ""

run_case \
    "Correctness: use before initialization" \
    "--week9" \
    "$ROOT_DIR/test/week9/test_week9_use_before_initialization.c" \
    1 \
    "used before initialization"

run_case \
    "Correctness: unreachable code" \
    "--week9" \
    "$ROOT_DIR/test/week9/test_week9_unreachable_code.c" \
    1 \
    "Unreachable statement detected"

run_case \
    "Correctness: unused variables" \
    "--week9" \
    "$ROOT_DIR/test/week9/test_week9_unused_variables.c" \
    1 \
    "declared but never used"

run_case \
    "Security: dangerous calls" \
    "--week10" \
    "$ROOT_DIR/test/week10/test_week10_dangerous_calls.c" \
    0 \
    "Dangerous function usage detected"

run_case \
    "Security: hard-coded credential" \
    "--week10" \
    "$ROOT_DIR/test/week10/test_week10_hardcoded_password.c" \
    0 \
    "Hard-coded credential detected"

run_case \
    "Security: weak RNG" \
    "--week10" \
    "$ROOT_DIR/test/week10/test_week10_weak_rng.c" \
    0 \
    "Weak random number generation detected"

run_case \
    "Validation: clean control has no security warnings" \
    "--week10" \
    "$ROOT_DIR/test/week10/test_week10_clean_control.c" \
    0 \
    "Parse successful" \
    "Security warning"

echo ""
echo "Summary: $pass_count passed, $fail_count failed"

if [ "$fail_count" -ne 0 ]; then
    exit 1
fi

exit 0
