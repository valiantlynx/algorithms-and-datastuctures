# Infix to Postfix Conversion and Evaluation

## Overview

This program converts an infix expression to a postfix expression using a stack and evaluates the postfix result. It supports basic arithmetic operations and functions like `log`, `sin`, and `cos`. The program also checks for invalid expressions with incorrect operator sequences.

## Features

- Converts complex infix expressions to postfix notation.
- Evaluates both infix and postfix expressions to provide the final result.
- Handles mathematical functions such as logarithms and trigonometric functions.
- Validates input expressions to prevent errors due to invalid operators.
- User-friendly interface with clear error messages for invalid inputs.

## Approach

### Infix to Postfix Conversion

1. **Scan the Infix Expression**: Each character is processed one at a time.
2. **Operands**: Directly add operands (numbers, variables) to the postfix output.
3. **Operators**: Use a stack to manage operators. Operators are pushed to the stack based on their precedence, and higher precedence operators are popped before pushing a lower precedence operator.
4. **Parentheses**: Handle parentheses by pushing opening brackets and popping until matching closing brackets are found.
5. **Functions**: Mathematical functions like `log`, `sin`, and `cos` are treated as operators with high precedence.
6. **Final Pop**: After scanning, any remaining operators are popped to the postfix expression.

### Postfix Evaluation

1. **Scan the Postfix Expression**: Each token is processed sequentially.
2. **Operands**: Push operands (numbers) onto a stack.
3. **Operators**: Pop two operands, apply the operator, and push the result back on the stack.
4. **Result**: The final result is the remaining value on the stack.

## Example Usage

```plaintext
Enter infix expression: (3+4)*2/2+4/2*8
Postfix expression: 3 4 + 2 * 2 / 4 2 / 8 * +
Result Postfix Expression: 23
```

## Error Handling

- The program checks for invalid sequences such as `++`, `--`, `//`, etc.
- Division by zero is explicitly handled and will generate an appropriate error message.
- Invalid or unsupported mathematical functions will also trigger an error.

## Requirements

- C++11 or higher.
- Standard library support for `<iostream>`, `<stack>`, `<string>`, `<cmath>`, and `<stdexcept>`.

## Compilation

Compile the program using a C++ compiler:

```bash
g++ infix_to_postfix.cpp -o infix_to_postfix -std=c++11
```

Run the executable:

```bash
./infix_to_postfix
```

## Authors

- Valiantlynx

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
