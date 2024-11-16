#include "variable.h"

vector<Variable> variables;
map<operator_k, Variable (*)(const Variable&, const Variable&)> operations;

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

    if (cntdigit + cntdot == expresion.size()) {
        return Variable("temp", "num", expresion);
    }

    return Variable("temp", "str", expresion);
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

Variable MakeOperation(const Variable &v1, const Variable &v2, const string &op) {
    if (v1.getType() != v2.getType()) {
        throw runtime_error("Cannot perform operation on different types");
    }

    if (v1.getType() == "num") {
        if (op == "+") {
            return add_Number(v1, v2);
        } else if (op == "-") {
            return sub_Number(v1, v2);
        } else if (op == "*") {
            return mul_Number(v1, v2);
        } else if (op == "/") {
            return div_Number(v1, v2);
        }
    } else if (v1.getType() == "str") {
        if (op == "+") {
            return add_String(v1, v2);
        }
    }

    throw runtime_error("Invalid operation");
}
