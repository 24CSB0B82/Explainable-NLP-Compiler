#ifndef EXPLANATION_ENGINE_H
#define EXPLANATION_ENGINE_H

#include <stdio.h>

typedef enum {
    DIAG_SEVERITY_ERROR,
    DIAG_SEVERITY_WARNING
} DiagnosticSeverity;

typedef enum {
    DIAG_RULE_SYNTAX_GENERIC,
    DIAG_RULE_MISSING_SEMICOLON,
    DIAG_RULE_UNDECLARED_IDENTIFIER,
    DIAG_RULE_REDECLARATION,
    DIAG_RULE_USE_BEFORE_INITIALIZATION,
    DIAG_RULE_UNREACHABLE_STATEMENT,
    DIAG_RULE_UNUSED_VARIABLE,
    DIAG_RULE_HARDCODED_CREDENTIAL,
    DIAG_RULE_DANGEROUS_FUNCTION,
    DIAG_RULE_WEAK_RANDOM,
    DIAG_RULE_PREDICTABLE_SEED
} DiagnosticRule;

void explanation_set_enabled(int enabled);
int explanation_is_enabled(void);
void explanation_emit(FILE *out,
                      DiagnosticSeverity severity,
                      DiagnosticRule rule,
                      int line,
                      const char *subject);

#endif
