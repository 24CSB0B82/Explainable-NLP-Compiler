# Week 13 - Sample Explanation Outputs

## Sample Inputs
- `test/week13/test_week13_syntax_explanation.c`
- `test/week13/test_week13_correctness_explanation.c`
- `test/week13/test_week13_security_explanation.c`

## Sample Output 1 - Syntax Explanation
```text
Syntax error at line 2: syntax error
Type: Syntax Error
Explanation: The input does not match the restricted C grammar expected by this compiler.
Fix: Check the nearby statement for missing symbols, misplaced operators, or incomplete blocks.
Location: line 2
```

## Sample Output 2 - Correctness Explanation
```text
Correctness error (line 4): use before initialization for 'value'
Type: Correctness Error (value)
Explanation: The variable is read before the program assigns any value to it on the reachable path.
Fix: Initialize the variable at declaration time or assign to it before using it.
Location: line 4
```

## Sample Output 3 - Security Explanation
```text
Security warning (line 1): hard-coded credential assigned to 'password'
Type: Security Warning (password)
Explanation: A sensitive identifier is assigned a literal value, which looks like a hard-coded secret.
Fix: Load credentials from a safer source such as configuration, environment variables, or secure storage.
Location: line 1
```

## How to Reproduce
```bash
make build
make week13
```

## Notes
- The explanation engine does not replace the original diagnostic.
- It adds a second layer that is easier for students, reviewers, and auditors to understand.
- Fix suggestions are intentionally short and actionable.
