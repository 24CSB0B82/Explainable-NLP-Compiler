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

## Security-Oriented Lexical Checks
- Sensitive identifiers flagged: `password`, `passwd`, `secret`, `token`, `api_key`
- Unsafe functions flagged: `gets`, `strcpy`, `strcat`, `sprintf`, `scanf`

## Week-6 Test Result Snapshot
Command used:
```bash
cd src
./compiler ../test/valid/test3.c
```
Observed diagnostics:
- `Security note (line 1): sensitive identifier 'token'`
- `Security note (line 2): sensitive identifier 'token'`
- `Security warning (line 3): unsafe function 'strcpy'`
- `Parse successful`
