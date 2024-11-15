#include "Sir.h"

void runConsole() {
    int lineCount = 0;
    string line;

    cout << "Welcome to Sir# Interpreter! Type 'exit' to quit.\n";
    while (true) {
        cout << "sir#[" << lineCount++ << "]> ";
        getline(cin, line);

        if (line == "exit") {
            cout << "Goodbye!\n";
            break;
        }

        try {
            cout << "Output: " << line << endl;
            //interpret(line);
        } catch (const exception &e) {
            cerr << "Error[Line " << lineCount << "]: " << e.what() << endl;
        }
    }
}

int main() {
    runConsole();
    return 0;
}
