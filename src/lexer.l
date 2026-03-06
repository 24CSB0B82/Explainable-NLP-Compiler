%{
#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char *dup_text(const char *text) {
    size_t n = strlen(text);
    char *copy = (char *)malloc(n + 1);
    if (copy == NULL) {
        return NULL;
    }
    memcpy(copy, text, n + 1);
    return copy;
}

static int is_sensitive_identifier(const char *name) {
    static const char *sensitive_names[] = {
        "password", "passwd", "secret", "token", "api_key"
    };
    int i;
    for (i = 0; i < (int)(sizeof(sensitive_names) / sizeof(sensitive_names[0])); i++) {
        if (strcmp(name, sensitive_names[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

static int is_unsafe_function(const char *name) {
    static const char *unsafe_functions[] = {
        "gets", "strcpy", "strcat", "sprintf", "scanf"
    };
    int i;
    for (i = 0; i < (int)(sizeof(unsafe_functions) / sizeof(unsafe_functions[0])); i++) {
        if (strcmp(name, unsafe_functions[i]) == 0) {
            return 1;
        }
    }
    return 0;
}
%}

%option noyywrap
%option yylineno

%%

"int"           { return INT; }
"char"          { return CHAR; }
"if"            { return IF; }
"else"          { return ELSE; }
"while"         { return WHILE; }

">="            { return GE; }
"<="            { return LE; }
"=="            { return EQ; }
"!="            { return NE; }
">"             { return GT; }
"<"             { return LT; }

"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return MUL; }
"/"             { return DIV; }
"="             { return ASSIGN; }

";"             { return SEMICOLON; }
","             { return COMMA; }
"("             { return LPAREN; }
")"             { return RPAREN; }
"{"             { return LBRACE; }
"}"             { return RBRACE; }

[0-9]+          {
                    yylval.ival = atoi(yytext);
                    return NUMBER;
                }

\"([^\\\"]|\\.)*\" {
                    yylval.sval = dup_text(yytext);
                    return STRING;
                }

[a-zA-Z_][a-zA-Z0-9_]*  {
                    if (is_sensitive_identifier(yytext)) {
                        fprintf(stderr, "Security note (line %d): sensitive identifier '%s'\n", yylineno, yytext);
                    }
                    if (is_unsafe_function(yytext)) {
                        fprintf(stderr, "Security warning (line %d): unsafe function '%s'\n", yylineno, yytext);
                    }
                    yylval.sval = dup_text(yytext);
                    return ID;
                }

"//".*          { /* ignore line comments */ }
"/*"([^*]|\*+[^*/])*\*+"/"    { /* ignore block comments */ }

[ \t\r\n]+      { /* ignore whitespace */ }

.               { fprintf(stderr, "Lexical error (line %d): unknown character '%s'\n", yylineno, yytext); }

%%
