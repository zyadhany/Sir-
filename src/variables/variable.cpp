#include "variable.h"

vector<Variable> variables;

Variable ConvertToVariable(const string &expresion){
    // todo: make type of intigers
    Variable var = Variable("temp", "str", expresion);
    return var;
}

Variable GetVariable(string name){
    int index = -1;
    for (int i = 0; i < variables.size(); i++) {
        if (variables[i].getName() == name) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        throw runtime_error("Variable " + name + " not found");
    }

    return variables[index];
}

Variable SetVariable(Variable var){
    int index = -1;
    for (int i = 0; i < variables.size(); i++) {
        if (variables[i].getName() == var.getName()) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        throw runtime_error("Variable " + var.getName() + " already exists");
    }
    variables.push_back(var);
    return var;
}
