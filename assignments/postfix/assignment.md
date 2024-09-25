# Assignment: Infix to Postfix Conversion Using Stack

## Problem Statement
How can we convert an infix expression to a postfix expression using a stack?

## Objective
Your task is to write a comprehensive program that converts an infix expression to a postfix expression using a stack. The program should handle complex infix expressions and calculate the final result for both infix and postfix expressions. For example, if the user enters the infix expression 

\[
(3 + 4) \cdot 2 / 2 + 4 / 2 \cdot 8,
\]

the program should print the result as \(23\).

## Marks Distribution
- **Infix to Postfix Conversion:** 2 Marks
- **Result of Basic Infix Equation:** 2 Marks  
  *Example:* 
  \[
  (3 + 46) \cdot 2 / 12 + 4 / 2 \cdot 8
  \]
- **Result of Complex Equation:** 2 Marks  
  *Example:* 
  \[
  3 \cdot \log(100) + \sin^2(90) - \cos(\log(1000)) + 2 - 3 \cdot 4 + 12
  \]
- **Extra Functionality:** 1 Mark  
  The program should not accept invalid operators like \(++, --, //, %%\). The user should be able to use the program without any prior programming knowledge.

## Algorithm Instructions

### Scan Characters One by One
1. If the character is an operand, copy it to the output of the postfix notation.
2. If the character is an opening parenthesis, push it to the stack.
3. If the character is a closing parenthesis, pop elements from the stack and add to the output until an opening parenthesis is encountered.
4. If the character is an operator:
   - While the stack is not empty and the precedence of the operator at the top of the stack is greater than or equal to the precedence of the current operator, pop the operator from the stack and add it to the output.
   - Push the current operator to the stack.

### Pop Remaining Operators
After scanning all characters, pop any remaining operators from the stack and add them to the output.

### Example
- **Infix:** 
  \[
  K + L - M \cdot N + (O^P) \cdot W / V / V \cdot T + Q
  \]
- **Postfix:** 
  \[
  KL + MN \cdot - OP^W \cdot V / V / T \cdot + Q +
  \]

## Additional Functionality
- Ensure the program handles complex mathematical functions like \(\log\), \(\sin\), and \(\cos\).
- Implement error handling for invalid inputs.
- Provide a user-friendly interface that guides the user through the process.

## Submission Guidelines
- Organize the code neatly with proper indentation and meaningful variable names.
- Include comments in the code to explain complex logic and functions.
- Provide a README file describing the Infix to Postfix conversion and the approach used.
- Zip the code files, README, and any additional resources into a single ZIP file and submit it on the assignment portal by the due date.

**Note:** You must work in a group; individual submissions without reason are unacceptable.
