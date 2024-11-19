#include "command.h"

map<string, Variable (*)(const Command &)> internal_functions = {
    {"print", builtin_print}
};

Variable builtin_print(const Command &command) {
    cout << command.expression << endl;
    return Variable();
}
