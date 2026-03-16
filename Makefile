CC = gcc
BISON = bison
FLEX = flex

SRC_DIR = src
TEST_DIR = test
WEEK7_VALID_DIR = $(TEST_DIR)/week7/valid
WEEK7_INVALID_DIR = $(TEST_DIR)/week7/invalid
WEEK8_DIR = $(TEST_DIR)/week8
WEEK9_DIR = $(TEST_DIR)/week9

PARSER_SRC = $(SRC_DIR)/parser.y
LEXER_SRC = $(SRC_DIR)/lexer.l
PARSER_C = $(SRC_DIR)/parser.tab.c
PARSER_H = $(SRC_DIR)/parser.tab.h
LEXER_C = $(SRC_DIR)/lex.yy.c
AST_C = $(SRC_DIR)/ast.c
SYMTAB_C = $(SRC_DIR)/symbol_table.c
CORRECTNESS_C = $(SRC_DIR)/correctness_analysis.c
COMPILER_BIN = $(SRC_DIR)/compiler

CFLAGS = -Wall -Wextra -std=gnu11
LDFLAGS = -lfl

.PHONY: all help build clean test test-valid test-invalid test-semantic test-week8 test-week9 week7 week8 week9

all: build

help:
	@echo "Targets:"
	@echo "  make build   - build the compiler"
	@echo "  make test    - run the full test suite"
	@echo "  make week7   - run week 7 syntax tests"
	@echo "  make week8   - run week 8 semantic tests"
	@echo "  make week9   - run week 9 correctness tests"
	@echo "  make clean   - remove generated build files"

build: $(COMPILER_BIN)

# Generated parser/lexer sources.
$(PARSER_C) $(PARSER_H): $(PARSER_SRC)
	cd $(SRC_DIR) && $(BISON) -d parser.y

$(LEXER_C): $(LEXER_SRC) $(PARSER_H)
	cd $(SRC_DIR) && $(FLEX) lexer.l

# Final compiler binary.
$(COMPILER_BIN): $(PARSER_C) $(LEXER_C) $(AST_C) $(SYMTAB_C) $(CORRECTNESS_C)
	$(CC) $(CFLAGS) $(PARSER_C) $(LEXER_C) $(AST_C) $(SYMTAB_C) $(CORRECTNESS_C) -o $(COMPILER_BIN) $(LDFLAGS)

# Aggregate targets.
test: test-valid test-invalid test-semantic

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
		./$(COMPILER_BIN) $$f || true; \
		echo ""; \
	done

# Week 9: correctness analysis.
test-week9: build
	@echo "Running week 9 correctness tests...\n"
	@for f in $(WEEK9_DIR)/*.c; do \
		echo "== $$f =="; \
		./$(COMPILER_BIN) $$f || true; \
		echo ""; \
	done

test-semantic: test-week8 test-week9

week7: build test-valid test-invalid

week8: build test-week8

week9: build test-week9

clean:
	rm -f $(COMPILER_BIN) $(PARSER_C) $(PARSER_H) $(LEXER_C)
