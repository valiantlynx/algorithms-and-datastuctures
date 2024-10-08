#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <cmath>
#include <stdexcept>
#include <sstream>
#include <map>

using namespace std;

// Higher precedence numbers indicate higher priority
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

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

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

bool validateInfix(const string &infix) {
    // Check for invalid operator sequences like ++, --, **, //, %%
    for (size_t i = 0; i < infix.length() - 1; ++i) {
        if ((infix[i] == '+' && infix[i + 1] == '+') || 
            (infix[i] == '-' && infix[i + 1] == '-') || 
            (infix[i] == '*' && infix[i + 1] == '*') || 
            (infix[i] == '/' && infix[i + 1] == '/') || 
            (infix[i] == '%' && infix[i + 1] == '%')) {
            return false;
        }
    }
    return true;
}

// handle mathematical functions
double applyFunction(const string &func, double value) {
    if (func == "log") return log10(value);
    if (func == "sin") return sin(value);
    if (func == "cos") return cos(value);
    throw runtime_error("function type not supported: " + func);
}

string infixToPostfix(const string &infix) {
    stack<string> operators;
    string postfix;
    string operand;

    for (size_t i = 0; i < infix.length(); ++i) {
        char c = infix[i];

        // numbers, variables, or functions
        if (isalnum(c) || c == '.') { // Check, a number or decimal
            operand += c;
        } else {
            if (!operand.empty()) {
                postfix += operand + ' ';
                operand.clear();
            }

            if (c == '(') {
                operators.push("(");
            } 
            // Handle closing parenthesis by popping until the matching '(' is found
            else if (c == ')') {
                while (!operators.empty() && operators.top() != "(") {
                    postfix += operators.top() + ' ';
                    operators.pop();
                }
                if (!operators.empty()) operators.pop(); // Pop the '('

            } 
            // checking precedence and popping higher precedence operators
            else if (isOperator(c)) {
                string op(1, c);
                while (!operators.empty() && precedence(operators.top()[0]) >= precedence(c)) {
                    postfix += operators.top() + ' ';
                    operators.pop();
                }
                operators.push(op);
            }
        }
    }
    // Add remaining operand to postfix
    if (!operand.empty()) {
        postfix += operand + ' ';
    }

    // Pop all remaining operators from the stac
    while (!operators.empty()) {
        postfix += operators.top() + ' ';
        operators.pop();
    }

    return postfix;
}

double evaluatePostfix(const string &postfix) {
    stack<double> values;
    stringstream ss(postfix);
    string token;

    // Read each token from the postfix expression
    while (ss >> token) {
        // If token is a number, push it onto the stack
        if (isdigit(token[0])) {
            values.push(stod(token));
        } 
        // If token is an operator, pop two values and apply the operator
        else if (isOperator(token[0])) {
            double b = values.top(); values.pop();
            double a = values.top(); values.pop();
            values.push(applyOperator(a, b, token[0]));
        }
    }

    // The result should be the only value left on the stack
    if (values.size() != 1) throw runtime_error("Invalid postfix evaluation");
    return values.top();
}

int main() {
    string infix;
    cout << "Enter infix expression: ";
    getline(cin, infix);

    try {
        // Validate infix expression for invalid operators
        if (!validateInfix(infix)) {
            cout << "Error: Invalid operator or operators." << endl;
            return 1;
        }
        // Convert infix to postfix
        string postfix = infixToPostfix(infix);
        cout << "Postfix expression: " << postfix << endl;
        // Evaluate the postfix expression
        double postfixResult = evaluatePostfix(postfix);
        cout << "Result Postfix Expression: " << postfixResult << endl;

    } catch (const exception &e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
