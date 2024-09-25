#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <cmath>
#include <map>
#include <stdexcept>

using namespace std;

// Function to return precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

// Function to perform arithmetic operations
double applyOperator(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) throw runtime_error("Division by zero");
            return a / b;
        case '^': return pow(a, b);
        default: throw runtime_error("Invalid operator");
    }
}

// Function to check if the character is a valid operator
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// Function to convert infix to postfix
string infixToPostfix(const string &infix) {
    stack<char> operators;
    string postfix;

    for (int i = 0; i < infix.length(); i++) {
        char c = infix[i];

        // If character is an operand (alphabet), add it to postfix
        if (isalnum(c)) {  // handles both digits and alphabet characters
            postfix += c;
            postfix += ' ';
        }
        // If character is '(', push it to stack
        else if (c == '(') {
            operators.push(c);
        }
        // If character is ')', pop until '(' is found
        else if (c == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top();
                postfix += ' ';
                operators.pop();
            }
            if (!operators.empty()) operators.pop(); // Remove '(' from stack
        }
        // If character is an operator
        else if (isOperator(c)) {
            while (!operators.empty() && precedence(operators.top()) >= precedence(c)) {
                postfix += operators.top();
                postfix += ' ';
                operators.pop();
            }
            operators.push(c);
        }
    }

    // Pop remaining operators from stack
    while (!operators.empty()) {
        postfix += operators.top();
        postfix += ' ';
        operators.pop();
    }

    return postfix;
}

// Function to evaluate a postfix expression
double evaluatePostfix(const string &postfix) {
    stack<double> values;
    string operand;

    for (char c : postfix) {
        if (isdigit(c) || c == '.') {
            operand += c;
        } else if (c == ' ' && !operand.empty()) {
            values.push(stod(operand));
            operand = "";
        } else if (isOperator(c)) {
            if (values.size() < 2) throw runtime_error("Invalid postfix expression");
            double b = values.top(); values.pop();
            double a = values.top(); values.pop();
            values.push(applyOperator(a, b, c));
        }
    }

    if (values.size() != 1) throw runtime_error("Invalid postfix evaluation");
    return values.top();
}

int main() {
    string infix;
    cout << "Enter infix expression: ";
    getline(cin, infix);  // Use getline to read the full expression including spaces

    try {
        string postfix = infixToPostfix(infix);
        cout << "Postfix expression: " << postfix << endl;

        // Uncomment below lines if you want to evaluate postfix with numeric values
        // double result = evaluatePostfix(postfix);
        // cout << "Result: " << result << endl;

    } catch (const exception &e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
