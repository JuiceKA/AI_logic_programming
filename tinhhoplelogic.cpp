#include <bits/stdc++.h>
using namespace std;

bool isOperator(char c) {
    return c == '^' || c == 'v' || c == '!' || c == '>'; 
}

bool isValidExpression(const string& expression) {
    int balance = 0;
    for (char c : expression) {
        if (c == '(') balance++;
        else if (c == ')') balance--;
        if (balance < 0) return false;
        if (!isOperator(c) && !isalpha(c) && c != ' ' && c != '(' && c != ')') return false;
    }
    return balance == 0;
}

bool evaluateExpressionSimple(const string& expression, const map<char, bool>& values) {
    auto applyOperator = [](char op, bool a, bool b = false) {
        if (op == '!') return !a;
        if (op == '^') return a && b;
        if (op == 'v') return a || b;
        if (op == '>') return !a || b;
        return false;
    };

    bool result = true; 
    bool currentValue = false;
    char lastOperator = '^'; 

    for (size_t i = 0; i < expression.length(); ++i) {
        char c = expression[i];

        if (isspace(c)) continue;

        if (isalpha(c)) {
            currentValue = values.at(c);
            result = applyOperator(lastOperator, result, currentValue);
        } else if (isOperator(c)) {
            lastOperator = c;
        } else if (c == '!') {
            ++i; 
            if (isalpha(expression[i])) {
                currentValue = !values.at(expression[i]);
                result = applyOperator(lastOperator, result, currentValue);
            }
        }
    }

    return result;
}

int main() {
    string expression;
    map<char, bool> values;

    cout << "Nhap bieu thuc logic (su dung ^ (va), v (hoac), ! (phu dinh), > (keo theo)): ";
    getline(cin, expression);

    if (!isValidExpression(expression)) {
        cout << "Bieu thuc khong hop le.\n";
        return 1;
    }

    cout << "Nhap gia tri cho cac bien (dang A 1 hoac B 0, nhap x de ket thuc): ";
    for (char var; cin >> var && var != 'x';) {
        int val;
        cin >> val;
        values[var] = val;
    }

    try {
        bool result = evaluateExpressionSimple(expression, values);
        cout << "Ket qua cua bieu thuc: " << (result ? "True" : "False") << "\n";
    } catch (const exception& e) {
        cerr << "Loi: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
