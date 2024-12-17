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

    Variable v1("tmp", "num", "10000000000000000000000");
    Variable v2("tmp", "num", "-0");
    Variable v3 = v1 * v2;
    cout<<v3.getValue()<<endl;

    Variable v11("tmp", "num", "10");
    Variable v22("tmp", "num", "-10");
    Variable v33 = v11 * v22;
    cout<<v33.getValue()<<endl;

//    runConsole();
    return 0;
}
