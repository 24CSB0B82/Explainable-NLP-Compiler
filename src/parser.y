%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"
#include "correctness_analysis.h"
#include "explanation_engine.h"
#include "security_audit.h"
#include "symbol_table.h"

int yylex(void);
int yyerror(const char *s);
extern int yylineno;
extern FILE *yyin;

static int syntax_error_count = 0;
static int semantic_error_count = 0;
static int security_warning_count = 0;
static int enable_correctness_analysis = 1;
static int enable_security_audit = 1;
static AstNode *ast_root = NULL;
static char current_decl_type[16] = "";

static char *dup_cstr(const char *s) {
    size_t n;
    char *copy;

    if (s == NULL) {
        return NULL;
    }

    n = strlen(s);
    copy = (char *)malloc(n + 1);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, s, n + 1);
    return copy;
}

static void set_decl_type(const char *type_name) {
    if (type_name == NULL) {
        current_decl_type[0] = '\0';
        return;
    }

    strncpy(current_decl_type, type_name, sizeof(current_decl_type) - 1);
    current_decl_type[sizeof(current_decl_type) - 1] = '\0';
}

static void report_undeclared(const char *name, int line) {
    fprintf(stderr, "Semantic error (line %d): '%s' used before declaration\n", line, name);
    explanation_emit(stderr, DIAG_SEVERITY_ERROR, DIAG_RULE_UNDECLARED_IDENTIFIER, line, name);
    semantic_error_count++;
}
%}

%code requires {
typedef struct AstNode AstNode;
}

%union {
    int ival;
    char *sval;
    AstNode *node;
}

%token INT CHAR IF ELSE WHILE
%token <sval> ID STRING
%token <ival> NUMBER
%token PLUS MINUS MUL DIV ASSIGN
%token GT LT GE LE EQ NE
%token LPAREN RPAREN LBRACE RBRACE
%token SEMICOLON COMMA

%type <node> program stmt_list_opt stmt_list stmt
%type <node> declaration_stmt declarator_list declarator assignment_stmt
%type <node> expr term factor if_stmt while_stmt condition block
%type <node> function_call_stmt arg_list
%type <sval> type relop

%nonassoc GT LT GE LE EQ NE
%left PLUS MINUS
%left MUL DIV

%%

program
    : stmt_list_opt {
        ast_root = ast_create(AST_PROGRAM, NULL, 0, yylineno);
        ast_add_child(ast_root, $1);
        $$ = ast_root;
    }
    ;

stmt_list_opt
    : stmt_list { $$ = $1; }
    | /* empty */ { $$ = NULL; }
    ;

stmt_list
    : stmt_list stmt { $$ = ast_append_sibling($1, $2); }
    | stmt { $$ = $1; }
    ;

stmt
    : declaration_stmt { $$ = $1; }
    | assignment_stmt { $$ = $1; }
    | if_stmt { $$ = $1; }
    | while_stmt { $$ = $1; }
    | function_call_stmt { $$ = $1; }
    | block { $$ = $1; }
    | error SEMICOLON { yyerror("discarded invalid statement"); yyerrok; $$ = NULL; }
    ;

declaration_stmt
    : type { set_decl_type($1); free($1); } declarator_list SEMICOLON {
        AstNode *decl_stmt = ast_create(AST_DECL_STMT, NULL, 0, yylineno);
        AstNode *type_node = ast_create(AST_TYPE, current_decl_type, 0, yylineno);

        ast_add_child(decl_stmt, type_node);
        ast_add_child(decl_stmt, $3);
        $$ = decl_stmt;
    }
    ;

type
    : INT { $$ = dup_cstr("int"); }
    | CHAR { $$ = dup_cstr("char"); }
    ;

declarator_list
    : declarator_list COMMA declarator { $$ = ast_append_sibling($1, $3); }
    | declarator { $$ = $1; }
    ;

declarator
    : ID {
        if (!symtab_declare($1, current_decl_type, yylineno)) {
            semantic_error_count++;
        }
        $$ = ast_create(AST_DECLARATOR, $1, 0, yylineno);
        free($1);
    }
    | ID ASSIGN expr {
        AstNode *decl = ast_create(AST_DECLARATOR, $1, 0, yylineno);
        if (!symtab_declare($1, current_decl_type, yylineno)) {
            semantic_error_count++;
        }
        ast_add_child(decl, $3);
        $$ = decl;
        free($1);
    }
    ;

assignment_stmt
    : ID ASSIGN expr SEMICOLON {
        AstNode *assign = ast_create(AST_ASSIGN_STMT, $1, 0, yylineno);
        if (symtab_lookup($1) == NULL) {
            report_undeclared($1, yylineno);
        }
        ast_add_child(assign, $3);
        $$ = assign;
        free($1);
    }
    | ID ASSIGN expr error {
        yyerror("missing ';' after assignment");
        yyerrok;
        free($1);
        $$ = NULL;
    }
    ;

expr
    : expr PLUS term {
        AstNode *op = ast_create(AST_BINOP, "+", 0, yylineno);
        ast_add_child(op, $1);
        ast_add_child(op, $3);
        $$ = op;
    }
    | expr MINUS term {
        AstNode *op = ast_create(AST_BINOP, "-", 0, yylineno);
        ast_add_child(op, $1);
        ast_add_child(op, $3);
        $$ = op;
    }
    | term { $$ = $1; }
    ;

term
    : term MUL factor {
        AstNode *op = ast_create(AST_BINOP, "*", 0, yylineno);
        ast_add_child(op, $1);
        ast_add_child(op, $3);
        $$ = op;
    }
    | term DIV factor {
        AstNode *op = ast_create(AST_BINOP, "/", 0, yylineno);
        ast_add_child(op, $1);
        ast_add_child(op, $3);
        $$ = op;
    }
    | factor { $$ = $1; }
    ;

factor
    : NUMBER { $$ = ast_create(AST_NUMBER, NULL, $1, yylineno); }
    | ID {
        if (symtab_lookup($1) == NULL) {
            report_undeclared($1, yylineno);
        }
        $$ = ast_create(AST_IDENTIFIER, $1, 0, yylineno);
        free($1);
    }
    | STRING {
        $$ = ast_create(AST_STRING, $1, 0, yylineno);
        free($1);
    }
    | LPAREN expr RPAREN { $$ = $2; }
    ;

if_stmt
    : IF LPAREN condition RPAREN block {
        AstNode *node = ast_create(AST_IF_STMT, NULL, 0, yylineno);
        ast_add_child(node, $3);
        ast_add_child(node, $5);
        $$ = node;
    }
    | IF LPAREN condition RPAREN block ELSE block {
        AstNode *node = ast_create(AST_IF_STMT, "else", 0, yylineno);
        ast_add_child(node, $3);
        ast_add_child(node, $5);
        ast_add_child(node, $7);
        $$ = node;
    }
    ;

while_stmt
    : WHILE LPAREN condition RPAREN block {
        AstNode *node = ast_create(AST_WHILE_STMT, NULL, 0, yylineno);
        ast_add_child(node, $3);
        ast_add_child(node, $5);
        $$ = node;
    }
    ;

condition
    : expr relop expr {
        AstNode *node = ast_create(AST_BINOP, $2, 0, yylineno);
        ast_add_child(node, $1);
        ast_add_child(node, $3);
        $$ = node;
        free($2);
    }
    | expr { $$ = $1; }
    ;

relop
    : GT { $$ = dup_cstr(">"); }
    | LT { $$ = dup_cstr("<"); }
    | GE { $$ = dup_cstr(">="); }
    | LE { $$ = dup_cstr("<="); }
    | EQ { $$ = dup_cstr("=="); }
    | NE { $$ = dup_cstr("!="); }
    ;

block
    : LBRACE { symtab_enter_scope(); } stmt_list_opt RBRACE {
        AstNode *node = ast_create(AST_BLOCK, NULL, 0, yylineno);
        ast_add_child(node, $3);
        $$ = node;
        symtab_exit_scope();
    }
    ;

function_call_stmt
    : ID LPAREN arg_list RPAREN SEMICOLON {
        AstNode *call = ast_create(AST_FUNC_CALL, $1, 0, yylineno);
        ast_add_child(call, $3);
        $$ = call;
        free($1);
    }
    | ID LPAREN arg_list RPAREN error {
        yyerror("missing ';' after function call");
        yyerrok;
        free($1);
        $$ = NULL;
    }
    ;

arg_list
    : arg_list COMMA expr { $$ = ast_append_sibling($1, $3); }
    | expr { $$ = $1; }
    | /* empty */ { $$ = NULL; }
    ;

%%

int main(int argc, char **argv) {
    int parse_result;
    const char *input_path = NULL;
    int i;

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--week8") == 0) {
            enable_correctness_analysis = 0;
            enable_security_audit = 0;
        } else if (strcmp(argv[i], "--week9") == 0) {
            enable_correctness_analysis = 1;
            enable_security_audit = 0;
        } else if (strcmp(argv[i], "--week10") == 0) {
            enable_correctness_analysis = 1;
            enable_security_audit = 1;
        } else if (strcmp(argv[i], "--week13") == 0) {
            enable_correctness_analysis = 1;
            enable_security_audit = 1;
            explanation_set_enabled(1);
        } else {
            input_path = argv[i];
        }
    }

    if (input_path != NULL) {
        yyin = fopen(input_path, "r");
        if (yyin == NULL) {
            fprintf(stderr, "Error: cannot open input file '%s'\n", input_path);
            return 1;
        }
    }

    symtab_init();
    parse_result = yyparse();
    if (parse_result == 0 && syntax_error_count == 0) {
        if (enable_correctness_analysis) {
            semantic_error_count += run_correctness_analysis(ast_root);
        }
        if (enable_security_audit) {
            security_warning_count = run_security_audit(ast_root);
        }
    }

    if (parse_result == 0 && syntax_error_count == 0 && semantic_error_count == 0) {
        printf("Parse successful\n");
        if (ast_root != NULL) {
            printf("\nAST:\n");
            ast_print(ast_root, 0);
        }
        if (security_warning_count > 0) {
            fprintf(stderr, "Security audit reported %d warning(s)\n", security_warning_count);
        }
    } else {
        if (parse_result == 0 && syntax_error_count > 0) {
            fprintf(stderr, "Parse completed with %d syntax error(s)\n", syntax_error_count);
        }
        if (semantic_error_count > 0) {
            fprintf(stderr, "Semantic analysis found %d issue(s)\n", semantic_error_count);
        }
        if (security_warning_count > 0) {
            fprintf(stderr, "Security audit reported %d warning(s)\n", security_warning_count);
        }
        parse_result = 1;
    }

    ast_free(ast_root);
    symtab_destroy();

    if (yyin != NULL && yyin != stdin) {
        fclose(yyin);
    }

    return parse_result;
}

int yyerror(const char *s) {
    syntax_error_count++;
    fprintf(stderr, "Syntax error at line %d: %s\n", yylineno, s);
    if (strcmp(s, "missing ';' after assignment") == 0 ||
        strcmp(s, "missing ';' after function call") == 0) {
        explanation_emit(stderr, DIAG_SEVERITY_ERROR, DIAG_RULE_MISSING_SEMICOLON, yylineno, NULL);
    } else {
        explanation_emit(stderr, DIAG_SEVERITY_ERROR, DIAG_RULE_SYNTAX_GENERIC, yylineno, NULL);
    }
    return 0;
}
