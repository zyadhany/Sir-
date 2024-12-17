#include "command.h"

map<string, Variable (*)(const Command &)> internal_functions = {
    {"print", builtin_print},
    {"var", builtin_var}  
};

Variable builtin_print(const Command &command) {
    Variable var(command.expression);
    cout << var.getValue() << endl;
    return Variable();
}

Variable builtin_var(const Command &command) {
    string name;
    string exp;

    if (command.expression.find("=", 0) != string::npos) {
        name = command.expression.substr(0, command.expression.find("=", 0));
        name = name.substr(0, name.find_last_not_of(" \t\n\r\f\v") + 1);
        exp = command.expression.substr(command.expression.find("=", 0) + 1);
    } else {
        throw runtime_error("Invalid variable declaration");
    }

    Variable var(exp);
    var.name = name;
    SetVariable(var);

    return var;
}
