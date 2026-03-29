#include "explanation_engine.h"

#include <stdio.h>

static int explanation_enabled = 0;

void explanation_set_enabled(int enabled) {
    explanation_enabled = enabled;
}

int explanation_is_enabled(void) {
    return explanation_enabled;
}

void explanation_emit(FILE *out,
                      DiagnosticSeverity severity,
                      DiagnosticRule rule,
                      int line,
                      const char *subject) {
    const char *level;
    const char *category;
    const char *headline = NULL;
    const char *explanation = NULL;
    const char *suggestion = NULL;

    if (!explanation_enabled) {
        return;
    }

    level = severity == DIAG_SEVERITY_ERROR ? "Error" : "Warning";
    category = "General";

    switch (rule) {
        case DIAG_RULE_SYNTAX_GENERIC:
            category = "Syntax";
            headline = "Input does not match the expected grammar.";
            explanation = "The input does not match the restricted C grammar expected by this compiler.";
            suggestion = "Check the nearby statement for missing symbols, misplaced operators, or incomplete blocks.";
            break;
        case DIAG_RULE_MISSING_SEMICOLON:
            category = "Syntax";
            headline = "Missing ';' after the statement.";
            explanation = "This statement is incomplete because the required semicolon terminator is missing.";
            suggestion = "Add ';' at the end of the statement.";
            break;
        case DIAG_RULE_UNDECLARED_IDENTIFIER:
            category = "Semantic";
            headline = "Variable is used before declaration.";
            explanation = "The program is using an identifier before declaring it in any visible scope.";
            suggestion = "Declare the variable before it is used or move the use into a scope where it is declared.";
            break;
        case DIAG_RULE_REDECLARATION:
            category = "Semantic";
            headline = "Variable is redeclared in the same scope.";
            explanation = "The same variable name is declared again in the same scope, so the symbol table rejects it.";
            suggestion = "Rename one declaration or remove the duplicate declaration.";
            break;
        case DIAG_RULE_USE_BEFORE_INITIALIZATION:
            category = "Correctness";
            headline = "Variable is used before initialization.";
            explanation = "The variable is read before the program assigns any value to it on the reachable path.";
            suggestion = "Initialize the variable at declaration time or assign to it before using it.";
            break;
        case DIAG_RULE_UNREACHABLE_STATEMENT:
            category = "Correctness";
            headline = "Unreachable statement detected.";
            explanation = "This statement is never executed because a constant condition makes the control-flow path unreachable.";
            suggestion = "Remove dead code or rewrite the condition so the branch can actually execute.";
            break;
        case DIAG_RULE_UNUSED_VARIABLE:
            category = "Correctness";
            headline = "Variable is declared but never used.";
            explanation = "The variable is declared but never read before the scope ends.";
            suggestion = "Remove the variable if it is unnecessary or use it in a meaningful expression.";
            break;
        case DIAG_RULE_HARDCODED_CREDENTIAL:
            category = "Security";
            headline = "Hard-coded credential detected.";
            explanation = "A sensitive identifier is assigned a literal value, which looks like a hard-coded secret.";
            suggestion = "Load credentials from a safer source such as configuration, environment variables, or secure storage.";
            break;
        case DIAG_RULE_DANGEROUS_FUNCTION:
            category = "Security";
            headline = "Dangerous function usage detected.";
            explanation = "This function is commonly associated with unsafe memory or input handling.";
            suggestion = "Replace it with a safer alternative or add explicit bounds and validation checks.";
            break;
        case DIAG_RULE_WEAK_RANDOM:
            category = "Security";
            headline = "Weak random number generation detected.";
            explanation = "The program uses rand(), which is predictable and weak for security-sensitive randomness.";
            suggestion = "Use a stronger random source for security-related behavior.";
            break;
        case DIAG_RULE_PREDICTABLE_SEED:
            category = "Security";
            headline = "Predictable random seed detected.";
            explanation = "The random generator is seeded with a constant expression, which makes the output sequence predictable.";
            suggestion = "Use a non-constant seed from a safer runtime source.";
            break;
        default:
            headline = "Compiler diagnostic reported.";
            explanation = "This diagnostic indicates a rule violation detected by the compiler.";
            suggestion = "Inspect the surrounding code and revise it to satisfy the reported rule.";
            break;
    }

    fprintf(out, "%s: %s", level, headline);
    if (subject != NULL) {
        fprintf(out, " Subject: '%s'.", subject);
    }
    fprintf(out, " Line: %d.\n", line);
    fprintf(out, "Type: %s %s\n", category, level);
    fprintf(out, "Explanation: %s\n", explanation);
    fprintf(out, "Fix: %s\n", suggestion);
    fprintf(out, "\n");
}
