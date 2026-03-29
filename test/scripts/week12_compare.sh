#!/usr/bin/env bash
set -u

ROOT_DIR="$(cd "$(dirname "$0")/../.." && pwd)"
COMPILER="$ROOT_DIR/src/compiler"
MATRIX_FILE="$ROOT_DIR/test/week12/case_matrix.tsv"
GCC_FLAGS=(
  -Wall
  -Wextra
  -std=gnu11
  -O1
  -fsyntax-only
  -Wuninitialized
  -Wmaybe-uninitialized
)

print_result_row() {
    printf "%-10s | %-11s | %-20s | %-20s | %s\n" "$1" "$2" "$3" "$4" "$5"
}

run_custom() {
    local mode="$1"
    local file="$2"
    local stdout_file
    local stderr_file

    stdout_file="$(mktemp)"
    stderr_file="$(mktemp)"

    if [ "$mode" = "-" ]; then
        "$COMPILER" "$ROOT_DIR/$file" >"$stdout_file" 2>"$stderr_file"
    else
        "$COMPILER" "$mode" "$ROOT_DIR/$file" >"$stdout_file" 2>"$stderr_file"
    fi

    cat "$stdout_file" "$stderr_file"
    rm -f "$stdout_file" "$stderr_file"
}

run_gcc_compare() {
    local file="$1"
    local temp_file

    temp_file="$(mktemp --suffix=.c)"
    {
        echo '#include <stdio.h>'
        echo '#include <stdlib.h>'
        echo '#include <string.h>'
        echo 'int main(void) {'
        cat "$ROOT_DIR/$file"
        echo 'return 0;'
        echo '}'
    } >"$temp_file"

    gcc "${GCC_FLAGS[@]}" "$temp_file" 2>&1 || true
    rm -f "$temp_file"
}

benchmark_command() {
    local label="$1"
    local iterations="$2"
    shift 2
    local total_ns=0
    local i
    local start_ns
    local end_ns
    local avg_ns
    local avg_ms

    for i in $(seq 1 "$iterations"); do
        start_ns="$(date +%s%N)"
        "$@" >/dev/null 2>/dev/null || true
        end_ns="$(date +%s%N)"
        total_ns=$((total_ns + end_ns - start_ns))
    done

    avg_ns=$((total_ns / iterations))
    avg_ms=$((avg_ns / 1000000))
    printf "%-18s : %d ms average over %d run(s)\n" "$label" "$avg_ms" "$iterations"
}

echo "Week 12 comparative evaluation"
echo ""
print_result_row "Case ID" "Category" "Our Compiler" "GCC" "Observation"
print_result_row "--------" "-----------" "--------------------" "--------------------" "-----------"

while IFS=$'\t' read -r case_id category mode file; do
    custom_output="$(run_custom "$mode" "$file")"
    gcc_output="$(run_gcc_compare "$file")"

    if printf "%s" "$custom_output" | grep -Eq "Type: Syntax Error|Type: Correctness Error|Type: Security Warning|Syntax error|Correctness error|Security warning|Parse successful"; then
        if printf "%s" "$custom_output" | grep -Eq "Type: Syntax Error|Syntax error"; then
            custom_status="syntax diagnostic"
        elif printf "%s" "$custom_output" | grep -Eq "Type: Correctness Error|Correctness error"; then
            custom_status="correctness diagnostic"
        elif printf "%s" "$custom_output" | grep -Eq "Type: Security Warning|Security warning"; then
            custom_status="security warning"
        else
            custom_status="clean success"
        fi
    else
        custom_status="no signal"
    fi

    if printf "%s" "$gcc_output" | grep -q "error:"; then
        gcc_status="gcc error"
    elif printf "%s" "$gcc_output" | grep -q "warning:"; then
        gcc_status="gcc warning"
    else
        gcc_status="no diagnostic"
    fi

    case "$category" in
        syntax)
            if [ "$gcc_status" = "gcc error" ]; then
                observation="both catch syntax issue"
            else
                observation="custom only"
            fi
            ;;
        correctness)
            if [ "$gcc_status" = "no diagnostic" ]; then
                observation="custom only"
            else
                observation="custom specific, gcc generic"
            fi
            ;;
        security)
            if [ "$gcc_status" = "no diagnostic" ]; then
                observation="custom security only"
            else
                observation="custom security, gcc generic"
            fi
            ;;
        control)
            if [ "$custom_status" = "clean success" ] && [ "$gcc_status" = "no diagnostic" ]; then
                observation="both accept"
            else
                observation="unexpected diagnostic"
            fi
            ;;
        *)
            observation="review manually"
            ;;
    esac

    print_result_row "$case_id" "$category" "$custom_status" "$gcc_status" "$observation"
done < "$MATRIX_FILE"

echo ""
echo "Week 12 performance metrics"
benchmark_command "our compiler" 5 "$COMPILER" --week10 "$ROOT_DIR/test/week10/test_week10_mixed_warnings.c"
benchmark_command "gcc baseline" 5 bash -lc "tmp=\$(mktemp --suffix=.c); { echo '#include <stdio.h>'; echo '#include <stdlib.h>'; echo '#include <string.h>'; echo 'int main(void) {'; cat '$ROOT_DIR/test/week10/test_week10_mixed_warnings.c'; echo 'return 0;'; echo '}'; } >\"\$tmp\"; gcc ${GCC_FLAGS[*]} \"\$tmp\" >/dev/null 2>/dev/null || true; rm -f \"\$tmp\""
