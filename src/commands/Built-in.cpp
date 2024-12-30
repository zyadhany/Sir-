#include "command.h"

map<string, Variable (*)(const Command &)> internal_functions = {
    {"print", builtin_print},
};

Variable builtin_print(const Command &command) {
    Variable var(command.expression);
    cout << var.getValue() << endl;
    return Variable();
}
