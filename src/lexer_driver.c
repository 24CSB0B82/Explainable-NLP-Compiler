#include <stdio.h>
#include <stdlib.h>

#include "parser.tab.h"
#include "tokens.h"

_Static_assert((int)TOK_INT == INT, "tokens.h mismatch: INT");
_Static_assert((int)TOK_CHAR == CHAR, "tokens.h mismatch: CHAR");
_Static_assert((int)TOK_IF == IF, "tokens.h mismatch: IF");
_Static_assert((int)TOK_ELSE == ELSE, "tokens.h mismatch: ELSE");
_Static_assert((int)TOK_WHILE == WHILE, "tokens.h mismatch: WHILE");
_Static_assert((int)TOK_ID == ID, "tokens.h mismatch: ID");
_Static_assert((int)TOK_STRING == STRING, "tokens.h mismatch: STRING");
_Static_assert((int)TOK_NUMBER == NUMBER, "tokens.h mismatch: NUMBER");
_Static_assert((int)TOK_PLUS == PLUS, "tokens.h mismatch: PLUS");
_Static_assert((int)TOK_MINUS == MINUS, "tokens.h mismatch: MINUS");
_Static_assert((int)TOK_MUL == MUL, "tokens.h mismatch: MUL");
_Static_assert((int)TOK_DIV == DIV, "tokens.h mismatch: DIV");
_Static_assert((int)TOK_ASSIGN == ASSIGN, "tokens.h mismatch: ASSIGN");
_Static_assert((int)TOK_GT == GT, "tokens.h mismatch: GT");
_Static_assert((int)TOK_LT == LT, "tokens.h mismatch: LT");
_Static_assert((int)TOK_GE == GE, "tokens.h mismatch: GE");
_Static_assert((int)TOK_LE == LE, "tokens.h mismatch: LE");
_Static_assert((int)TOK_EQ == EQ, "tokens.h mismatch: EQ");
_Static_assert((int)TOK_NE == NE, "tokens.h mismatch: NE");
_Static_assert((int)TOK_LPAREN == LPAREN, "tokens.h mismatch: LPAREN");
_Static_assert((int)TOK_RPAREN == RPAREN, "tokens.h mismatch: RPAREN");
_Static_assert((int)TOK_LBRACE == LBRACE, "tokens.h mismatch: LBRACE");
_Static_assert((int)TOK_RBRACE == RBRACE, "tokens.h mismatch: RBRACE");
_Static_assert((int)TOK_SEMICOLON == SEMICOLON, "tokens.h mismatch: SEMICOLON");
_Static_assert((int)TOK_COMMA == COMMA, "tokens.h mismatch: COMMA");

extern FILE *yyin;
extern char *yytext;
extern int yylex(void);
extern int yylineno;

YYSTYPE yylval;

static const char *token_name(int token) {
    switch (token) {
        case TOK_INT: return "INT";
        case TOK_CHAR: return "CHAR";
        case TOK_IF: return "IF";
        case TOK_ELSE: return "ELSE";
        case TOK_WHILE: return "WHILE";
        case TOK_ID: return "ID";
        case TOK_STRING: return "STRING";
        case TOK_NUMBER: return "NUMBER";
        case TOK_PLUS: return "PLUS";
        case TOK_MINUS: return "MINUS";
        case TOK_MUL: return "MUL";
        case TOK_DIV: return "DIV";
        case TOK_ASSIGN: return "ASSIGN";
        case TOK_GT: return "GT";
        case TOK_LT: return "LT";
        case TOK_GE: return "GE";
        case TOK_LE: return "LE";
        case TOK_EQ: return "EQ";
        case TOK_NE: return "NE";
        case TOK_LPAREN: return "LPAREN";
        case TOK_RPAREN: return "RPAREN";
        case TOK_LBRACE: return "LBRACE";
        case TOK_RBRACE: return "RBRACE";
        case TOK_SEMICOLON: return "SEMICOLON";
        case TOK_COMMA: return "COMMA";
        default: return "UNKNOWN";
    }
}

static void print_token(int token) {
    printf("line = %d token = %s lexeme = '%s'", yylineno, token_name(token), yytext);

    if (token == TOK_NUMBER) {
        printf(" value=%d", yylval.ival);
    } else if (token == TOK_ID || token == TOK_STRING) {
        printf(" value=%s", yylval.sval);
    }

    putchar('\n');
}

int main(int argc, char **argv) {
    int token;

    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (yyin == NULL) {
            fprintf(stderr, "Error: cannot open input file '%s'\n", argv[1]);
            return 1;
        }
    }

    while ((token = yylex()) != 0) {
        print_token(token);
        if (token == TOK_ID || token == TOK_STRING) {
            free(yylval.sval);
            yylval.sval = NULL;
        }
    }

    if (yyin != NULL && yyin != stdin) {
        fclose(yyin);
    }

    return 0;
}
