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

    Variable v1 = ConvertToVariable("444, 4");
    Variable v2 = ConvertToVariable("qq");
    Variable v3 = ConvertToVariable("sfdg");
    

    v3 = v1 + v3;

    v3.print();

    return 0;
}

// Cc$01011