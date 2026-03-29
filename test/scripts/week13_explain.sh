#!/usr/bin/env bash
set -u

ROOT_DIR="$(cd "$(dirname "$0")/../.." && pwd)"
COMPILER="$ROOT_DIR/src/compiler"

echo "Week 13 explanation samples"
echo ""

for file in "$ROOT_DIR"/test/week13/*.c; do
    echo "== ${file#$ROOT_DIR/} =="
    "$COMPILER" --week13 "$file" 2>&1 || true
    echo ""
done
