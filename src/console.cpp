#include "Sir.h"

/**
 * @brief Run the Sir# interpreter console.
 * 
 * @return void
 */
void runConsole() {
    int lineCount = 0;
    string line;

    cout << "Welcome to Sir# Interpreter! Type 'exit' to quit.\n";
    while (true) {
        cout << "sir#[" << lineCount++ << "]> ";
        
        if (!getline(cin, line)) {
            cout << "Goodbye!\n";
            break;
        }

        if (line == "exit") {
            cout << "Goodbye!\n";
            break;
        }

        try {
            interpret(line);
        } catch (const exception &e) {
            cerr << "Error[Line " << lineCount << "]: " << e.what() << endl;
        }
    }
}

int main(int argc, char *argv[]) {
    // runConsole();

    // test oprator

    while (true)
    {
        string s1, s2;
        string opp;
        cin >> s1 >> s2 >> opp;

        Variable v1 = ConvertToVariable(s1);
        Variable v2 = ConvertToVariable(s2);
        Variable res = v1;

        if (opp == "+") {
            res = v1 + v2;
        } else if (opp == "-") {
            res = v1 - v2;
        } else if (opp == "*") {
            res = v1 * v2;
        } else if (opp == "/") {
            res = v1 / v2;
        } else if (opp == "%") {
            res = v1 % v2;
        } else if (opp == "&") {
            res = v1 & v2;
        } else if (opp == "|") {
            res = v1 | v2;
        } else if (opp == "^") {
            res = v1 ^ v2;
        } else if (opp == "<<") {
            res = v1 << v2;
        } else if (opp == ">>") {
            res = v1 >> v2;
        } 
        else if (opp == "<") {
            res = v1 < v2;
        } else if (opp == ">") {
            res = v1 > v2;
        } else if (opp == "<=") {
            res = v1 <= v2;
        } else if (opp == ">=") {
            res = v1 >= v2;
        } else if (opp == "==") {
            res = v1 == v2;
        } else if (opp == "!=") {
            res = v1 != v2;
        } else if (opp == "&&") {
            res = v1 && v2;
        } else if (opp == "||") {
            res = v1 || v2;
        } else if (opp == "!") {
            res = !v1;
        } else if (opp == "~") {
            res = ~v1;
        }
        else {
            cout << "Invalid operation\n";
            continue;
        }

        cout << res << '\n';
    }
    
    return 0;
}

// Cc$01011