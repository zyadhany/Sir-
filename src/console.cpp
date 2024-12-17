#include "Sir.h"

SirGlobal sirGlobal;

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
            cout << "Error: " << e.what() << endl;
            // cerr << "Error[Line " << lineCount << "]: " << e.what() << endl;
        }
    }
}

int main(int argc, char *argv[]) {

    /*Variable v1("v1", "num", "15");
    Variable v2("v2", "num", "2");
    Variable v3 = v1 / v2;
    cout<<v3.getValue()<<endl;*/

    runConsole();
    return 0;
}
