CC = gcc
BISON = bison
FLEX = flex

SRC_DIR = src
TEST_DIR = test

PARSER_SRC = $(SRC_DIR)/parser.y
LEXER_SRC = $(SRC_DIR)/lexer.l
PARSER_C = $(SRC_DIR)/parser.tab.c
PARSER_H = $(SRC_DIR)/parser.tab.h
LEXER_C = $(SRC_DIR)/lex.yy.c
AST_C = $(SRC_DIR)/ast.c
SYMTAB_C = $(SRC_DIR)/symbol_table.c
COMPILER_BIN = $(SRC_DIR)/compiler

CFLAGS = -Wall -Wextra -std=gnu11
LDFLAGS = -lfl

.PHONY: all build clean test test-valid test-invalid test-semantic week7 week8

all: build

build: $(COMPILER_BIN)

$(PARSER_C) $(PARSER_H): $(PARSER_SRC)
	cd $(SRC_DIR) && $(BISON) -d parser.y

$(LEXER_C): $(LEXER_SRC) $(PARSER_H)
	cd $(SRC_DIR) && $(FLEX) lexer.l

$(COMPILER_BIN): $(PARSER_C) $(LEXER_C) $(AST_C) $(SYMTAB_C)
	$(CC) $(CFLAGS) $(PARSER_C) $(LEXER_C) $(AST_C) $(SYMTAB_C) -o $(COMPILER_BIN) $(LDFLAGS)

test: test-valid test-invalid test-semantic

test-valid: build
	@echo "Running valid tests..."
	@for f in $(TEST_DIR)/valid/*.c; do \
		echo "== $$f =="; \
		./$(COMPILER_BIN) $$f; \
	done

test-invalid: build
	@echo "Running invalid syntax tests..."
	@for f in $(TEST_DIR)/invalid/*.c; do \
		echo "== $$f =="; \
		./$(COMPILER_BIN) $$f || true; \
	done

test-semantic: build
	@echo "Running semantic tests..."
	@for f in $(TEST_DIR)/errors/*.c; do \
		echo "== $$f =="; \
		./$(COMPILER_BIN) $$f || true; \
	done

week7: build test-valid test-invalid

week8: build test-semantic

clean:
	rm -f $(COMPILER_BIN) $(PARSER_C) $(PARSER_H) $(LEXER_C)
