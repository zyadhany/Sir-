#include "command.h"

map<string, Variable (*)(const Command &)> internal_functions = {
    {"print", builtin_print},
    {"var", builtin_var}  
};

Variable builtin_print(const Command &command) {
    cout << command.expression << endl;
    return Variable();
}

Variable builtin_var(const Command &command) {
    string name = "";
    for (int i = 0; i < command.expression.size(); i++) {
        if (command.expression[i] == ' ') break;
        name += command.expression[i];
    }
    string expression = command.expression.substr(name.size() + 1);
    Variable var = SetVariable(Variable(name, expression));
    return var;
}
