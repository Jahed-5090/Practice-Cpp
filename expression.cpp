#include <iostream>
#include <stack>
#include <string>
#include <algorithm>
#include <cmath>
#include <cctype>

using namespace std;

// --- NEW HELPER FUNCTIONS ---

// 1. Function to safely ignore spaces and specific punctuation
bool isIgnored(char c) {
    // isspace() handles standard spaces, tabs, and newlines
    return isspace(c) || c == ',' || c == '.' || c == '\'';
}

// 2. Function to verify if a character is a mathematical operator
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// ----------------------------

// Function to get the precedence of operators
int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return -1;
}

// Function to perform basic arithmetic operations
int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        case '^': return pow(a, b);
    }
    return 0;
}

// 1. Transform Infix to Postfix
string infixToPostfix(string s) {
    stack<char> st;
    string result;
    
    for (int i = 0; i < s.length(); i++) {
        char c = s[i];
        
        // NEW: Skip spaces and extra formatting characters
        if (isIgnored(c)) continue;
        
        // If operand, add to output
        if (isalnum(c)) {
            result += c;
        }
        // If '(', push to stack
        else if (c == '(') {
            st.push('(');
        }
        // If ')', pop to output until '(' is encountered
        else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                result += st.top();
                st.pop();
            }
            if (!st.empty()) st.pop(); // Pop '('
        }
        // If valid operator (NEW: explicit check prevents crashes from stray chars)
        else if (isOperator(c)) {
            while (!st.empty() && precedence(c) <= precedence(st.top())) {
                result += st.top();
                st.pop();
            }
            st.push(c);
        }
    }
    // Pop remaining operators
    while (!st.empty()) {
        result += st.top();
        st.pop();
    }
    return result;
}

// 2. Transform Infix to Prefix
string infixToPrefix(string s) {
    reverse(s.begin(), s.end());
    
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(') {
            s[i] = ')';
        } else if (s[i] == ')') {
            s[i] = '(';
        }
    }
    
    // infixToPostfix already handles ignoring spaces, so we don't need to do it here
    string postfix = infixToPostfix(s);
    reverse(postfix.begin(), postfix.end());
    
    return postfix;
}

// 3. Evaluate Postfix Expression
int evaluatePostfix(string exp) {
    stack<int> st;
    
    for (int i = 0; i < exp.length(); i++) {
        char c = exp[i];
        
        // NEW: Skip spaces and extra formatting characters
        if (isIgnored(c)) continue;
        
        if (isdigit(c)) {
            st.push(c - '0'); 
        } 
        // NEW: Only pop from stack if it is definitively an operator
        else if (isOperator(c)) {
            int val1 = st.top(); st.pop(); 
            int val2 = st.top(); st.pop(); 
            st.push(applyOp(val2, val1, c)); 
        }
    }
    return st.top();
}

// 4. Evaluate Prefix Expression
int evaluatePrefix(string exp) {
    stack<int> st;
    
    for (int i = exp.length() - 1; i >= 0; i--) {
        char c = exp[i];
        
        // NEW: Skip spaces and extra formatting characters
        if (isIgnored(c)) continue;
        
        if (isdigit(c)) {
            st.push(c - '0');
        } 
        else if (isOperator(c)) {
            int val1 = st.top(); st.pop(); 
            int val2 = st.top(); st.pop(); 
            st.push(applyOp(val1, val2, c)); 
        }
    }
    return st.top();
}

int main() {
    // Test Case 1: Added spaces and punctuation to test the filter
    string infixExp = "A + (B * C - (D / E ^ F) * G) * H , ' .";
    cout << "--- Transformations ---" << endl;
    cout << "Original Infix: " << infixExp << endl;
    cout << "Postfix: " << infixToPostfix(infixExp) << endl;
    cout << "Prefix:  " << infixToPrefix(infixExp) << endl << endl;

    // Test Case 2: Added spaces, commas, and dots
    string postfixExp = "5, 6. 2 + * 4 / ' "; 
    cout << "--- Evaluations ---" << endl;
    cout << "Evaluating Postfix (" << postfixExp << "): " << evaluatePostfix(postfixExp) << endl;

    // Test Case 3: Added spaces
    string prefixExp = "/ * 5 + 6 2 4";
    cout << "Evaluating Prefix  (" << prefixExp << "): " << evaluatePrefix(prefixExp) << endl;

    return 0;
}