#include "variable.h"

vector<Variable> variables;

Variable ConvertToVariable(const string &expresion){
    int cntdot = 0;
    int cntdigit = 0;
    
    for (auto c : expresion) {
        if (c == '.') {
            cntdot++;
        } else if (isdigit(c)) {
            cntdigit++;
        }
    }


    if (expresion.size() > 0 && expresion[0] == '-') cntdigit++;

    Variable var = Variable("temp", "string", expresion);
    if (cntdigit + cntdot == expresion.size()) {
        var = Variable("temp", "number", expresion);
    } else {

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
