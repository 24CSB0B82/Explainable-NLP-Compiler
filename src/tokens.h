#ifndef TOKENS_H
#define TOKENS_H

/*
 * Project token set aligned with src/parser.y and src/lexer.l.
 * Keep this in sync with Bison %token declarations.
 */
enum project_tokens {
    TOK_INT = 258,
    TOK_CHAR,
    TOK_IF,
    TOK_ELSE,
    TOK_WHILE,
    TOK_ID,
    TOK_NUMBER,
    TOK_STRING,
    TOK_PLUS,
    TOK_MINUS,
    TOK_MUL,
    TOK_DIV,
    TOK_ASSIGN,
    TOK_GT,
    TOK_LT,
    TOK_GE,
    TOK_LE,
    TOK_EQ,
    TOK_NE,
    TOK_LPAREN,
    TOK_RPAREN,
    TOK_LBRACE,
    TOK_RBRACE,
    TOK_SEMICOLON,
    TOK_COMMA
};

#endif /* TOKENS_H */
