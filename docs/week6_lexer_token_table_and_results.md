# Week 6 - Lexical Analysis Implementation

## Token Table
| Category | Tokens |
|---|---|
| Keywords | `INT`, `CHAR`, `IF`, `ELSE`, `WHILE` |
| Identifiers | `ID` |
| Literals | `NUMBER`, `STRING` |
| Arithmetic Operators | `PLUS`, `MINUS`, `MUL`, `DIV` |
| Assignment | `ASSIGN` |
| Relational Operators | `GT`, `LT`, `GE`, `LE`, `EQ`, `NE` |
| Delimiters | `SEMICOLON`, `COMMA`, `LPAREN`, `RPAREN`, `LBRACE`, `RBRACE` |

## Implemented Lexical Rules
- Ignores whitespace.
- Ignores `//` and `/* ... */` comments.
- Recognizes identifiers, numbers, and escaped-string literals.
- Reports lexical error for unknown characters.

## Security Note
- The lexer now focuses only on tokenization and lexical errors.
- Security detection for sensitive identifiers and unsafe functions was moved to the dedicated week-10 security audit module.

## Week-6 Token Dump
- Use the standalone lexer driver to print tokens without invoking the parser.
- This keeps week 6 isolated from later parser and analysis stages.

## Week-6 Test Result Snapshot
Command used:
```bash
make week6
```
Observed diagnostics:
- token output includes token name, source lexeme, line number, and literal value for `NUMBER`, `ID`, and `STRING`
