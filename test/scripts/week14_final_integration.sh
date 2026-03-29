#!/usr/bin/env bash
set -u

ROOT_DIR="$(cd "$(dirname "$0")/../.." && pwd)"
COMPILER="$ROOT_DIR/src/compiler"
MATRIX_FILE="$ROOT_DIR/test/week14/nlp_case_matrix.tsv"

pass_count=0
fail_count=0

run_case() {
    local case_id="$1"
    local category="$2"
    local mode="$3"
    local file="$4"
    local expected_exit="$5"
    local expected_pattern="$6"
    local output_file
    local exit_code

    output_file="$(mktemp)"

    if [ "$mode" = "-" ]; then
        "$COMPILER" "$ROOT_DIR/$file" >"$output_file" 2>&1
    else
        "$COMPILER" "$mode" "$ROOT_DIR/$file" >"$output_file" 2>&1
    fi
    exit_code=$?

    if [ "$exit_code" -ne "$expected_exit" ]; then
        echo "[FAIL] $case_id ($category)"
        echo "  Expected exit: $expected_exit, actual exit: $exit_code"
        sed -n '1,80p' "$output_file"
        fail_count=$((fail_count + 1))
        rm -f "$output_file"
        return
    fi

    if ! grep -q "$expected_pattern" "$output_file"; then
        echo "[FAIL] $case_id ($category)"
        echo "  Missing expected pattern: $expected_pattern"
        sed -n '1,80p' "$output_file"
        fail_count=$((fail_count + 1))
        rm -f "$output_file"
        return
    fi

    if [ "$category" != "control" ]; then
        if ! grep -q '^Explanation:' "$output_file" || ! grep -q '^Fix:' "$output_file"; then
            echo "[FAIL] $case_id ($category)"
            echo "  NLP explanation block is incomplete"
            sed -n '1,80p' "$output_file"
            fail_count=$((fail_count + 1))
            rm -f "$output_file"
            return
        fi
    fi

    if grep -q '^AST:' "$output_file"; then
        echo "[FAIL] $case_id ($category)"
        echo "  AST output should not appear in week 14 mode"
        sed -n '1,80p' "$output_file"
        fail_count=$((fail_count + 1))
        rm -f "$output_file"
        return
    fi

    echo "[PASS] $case_id ($category)"
    pass_count=$((pass_count + 1))
    rm -f "$output_file"
}

echo "Week 14 final integration run"
echo ""

while IFS=$'\t' read -r case_id category mode file expected_exit expected_pattern; do
    run_case "$case_id" "$category" "$mode" "$file" "$expected_exit" "$expected_pattern"
done < "$MATRIX_FILE"

echo ""
echo "Summary: $pass_count passed, $fail_count failed"

if [ "$fail_count" -ne 0 ]; then
    exit 1
fi
