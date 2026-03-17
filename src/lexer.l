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
                    yylval.sval = dup_text(yytext);
                    return ID;
                }

"//".*          { /* ignore line comments */ }
"/*"([^*]|\*+[^*/])*\*+"/"    { /* ignore block comments */ }

[ \t\r\n]+      { /* ignore whitespace */ }

.               { fprintf(stderr, "Lexical error (line %d): unknown character '%s'\n", yylineno, yytext); }

%%
