CC = gcc
BISON = bison
FLEX = flex

SRC_DIR = src
TEST_DIR = test
WEEK6_DIR = $(TEST_DIR)/week6
WEEK7_VALID_DIR = $(TEST_DIR)/week7/valid
WEEK7_INVALID_DIR = $(TEST_DIR)/week7/invalid
WEEK8_DIR = $(TEST_DIR)/week8
WEEK9_DIR = $(TEST_DIR)/week9
WEEK10_DIR = $(TEST_DIR)/week10
WEEK12_DIR = $(TEST_DIR)/week12
WEEK13_DIR = $(TEST_DIR)/week13

PARSER_SRC = $(SRC_DIR)/parser.y
LEXER_SRC = $(SRC_DIR)/lexer.l
PARSER_C = $(SRC_DIR)/parser.tab.c
PARSER_H = $(SRC_DIR)/parser.tab.h
LEXER_C = $(SRC_DIR)/lex.yy.c
LEXER_DRIVER_C = $(SRC_DIR)/lexer_driver.c
AST_C = $(SRC_DIR)/ast.c
SYMTAB_C = $(SRC_DIR)/symbol_table.c
CORRECTNESS_C = $(SRC_DIR)/correctness_analysis.c
SECURITY_AUDIT_C = $(SRC_DIR)/security_audit.c
COMPILER_BIN = $(SRC_DIR)/compiler
LEXER_DRIVER_BIN = $(SRC_DIR)/lexer_driver
TEST_SCRIPT_DIR = $(TEST_DIR)/scripts
WEEK11_SCRIPT = $(TEST_SCRIPT_DIR)/week11_validate.sh
WEEK12_SCRIPT = $(TEST_SCRIPT_DIR)/week12_compare.sh
WEEK13_SCRIPT = $(TEST_SCRIPT_DIR)/week13_explain.sh

CFLAGS = -Wall -Wextra -std=gnu11
LDFLAGS = -lfl

.PHONY: all help build clean test test-week6 test-valid test-invalid test-semantic test-week8 test-week9 test-week10 test-week11 test-week12 test-week13 week6 week7 week8 week9 week10 week11 week12 week13

all: build

help:
	@echo "Targets:"
	@echo "  make build   - build the compiler"
	@echo "  make test    - run the full test suite"
	@echo "  make week6   - run week 6 lexer token tests"
	@echo "  make week7   - run week 7 syntax tests"
	@echo "  make week8   - run week 8 semantic tests"
	@echo "  make week9   - run week 9 correctness tests"
	@echo "  make week10  - run week 10 security warning tests"
	@echo "  make week11  - run week 11 validation summary"
	@echo "  make week12  - run week 12 comparison and metrics"
	@echo "  make week13  - run week 13 explanation samples"
	@echo "  make clean   - remove generated build files"

build: $(COMPILER_BIN)

# Generated parser/lexer sources.
$(PARSER_C) $(PARSER_H): $(PARSER_SRC)
	cd $(SRC_DIR) && $(BISON) -d parser.y

$(LEXER_C): $(LEXER_SRC) $(PARSER_H)
	cd $(SRC_DIR) && $(FLEX) lexer.l

# Standalone lexer driver for week 6 token dumps.
$(LEXER_DRIVER_BIN): $(LEXER_C) $(LEXER_DRIVER_C)
	$(CC) $(CFLAGS) $(LEXER_DRIVER_C) $(LEXER_C) -o $(LEXER_DRIVER_BIN) $(LDFLAGS)

# Final compiler binary.
$(COMPILER_BIN): $(PARSER_C) $(LEXER_C) $(AST_C) $(SYMTAB_C) $(CORRECTNESS_C) $(SECURITY_AUDIT_C) $(SRC_DIR)/explanation_engine.c
	$(CC) $(CFLAGS) $(PARSER_C) $(LEXER_C) $(AST_C) $(SYMTAB_C) $(CORRECTNESS_C) $(SECURITY_AUDIT_C) $(SRC_DIR)/explanation_engine.c -o $(COMPILER_BIN) $(LDFLAGS)

# Aggregate targets.
test: test-week6 test-valid test-invalid test-semantic test-week10 test-week11 test-week12 test-week13

# Week 6: lexer token dump validation.
test-week6: $(LEXER_DRIVER_BIN)
	@echo "Running week 6 lexer token tests...\n"
	@for f in $(WEEK6_DIR)/*.c; do \
		echo "== $$f =="; \
		./$(LEXER_DRIVER_BIN) $$f; \
		echo ""; \
	done

# Week 7: lexer/parser validation.
test-valid: build
	@echo "Running week 7 valid tests...\n"
	@for f in $(WEEK7_VALID_DIR)/*.c; do \
		echo "== $$f =="; \
		./$(COMPILER_BIN) $$f; \
		echo ""; \
	done

test-invalid: build
	@echo "Running week 7 invalid syntax tests...\n"
	@for f in $(WEEK7_INVALID_DIR)/*.c; do \
		echo "== $$f =="; \
		./$(COMPILER_BIN) $$f || true; \
		echo ""; \
	done

# Week 8: symbol-table and early semantic checks.
test-week8: build
	@echo "Running week 8 semantic tests...\n"
	@for f in $(WEEK8_DIR)/*.c; do \
		echo "== $$f =="; \
		./$(COMPILER_BIN) --week8 $$f || true; \
		echo ""; \
	done

# Week 9: correctness analysis.
test-week9: build
	@echo "Running week 9 correctness tests...\n"
	@for f in $(WEEK9_DIR)/*.c; do \
		echo "== $$f =="; \
		./$(COMPILER_BIN) --week9 $$f || true; \
		echo ""; \
	done

# Week 10: security audit warnings.
test-week10: build
	@echo "Running week 10 security tests...\n"
	@for f in $(WEEK10_DIR)/*.c; do \
		echo "== $$f =="; \
		./$(COMPILER_BIN) --week10 $$f || true; \
		echo ""; \
	done

# Week 11: validation summary over correctness and security suites.
test-week11: build
	@echo "Running week 11 validation...\n"
	@bash $(WEEK11_SCRIPT)

# Week 12: comparison with traditional compiler diagnostics and performance metrics.
test-week12: build
	@echo "Running week 12 comparison...\n"
	@bash $(WEEK12_SCRIPT)

# Week 13: explanation engine samples.
test-week13: build
	@echo "Running week 13 explanations...\n"
	@bash $(WEEK13_SCRIPT)

test-semantic: test-week8 test-week9

week6: test-week6

week7: build test-valid test-invalid

week8: build test-week8

week9: build test-week9

week10: build test-week10

week11: build test-week11

week12: build test-week12

week13: build test-week13

clean:
	rm -f $(COMPILER_BIN) $(LEXER_DRIVER_BIN) $(PARSER_C) $(PARSER_H) $(LEXER_C)
