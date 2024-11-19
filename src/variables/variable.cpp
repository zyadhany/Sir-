#include "variable.h"

vector<Variable> variables;

map<operator_k, Variable (*)(const Variable&, const Variable&)> operations = {
    {operator_k("+", "num", "num"), add_Number},
    {operator_k("-", "num", "num"), sub_Number},
    {operator_k("*", "num", "num"), mul_Number},
    {operator_k("/", "num", "num"), div_Number},
    {operator_k("+", "str", "str"), add_String},
    {operator_k("-", "str", "str"), sub_String},
    {operator_k("*", "str", "num"), mul_str_num},
    {operator_k("*", "num", "str"), mul_num_str},
    {operator_k("%", "num", "num"), mod_Number},
    {operator_k("&", "num", "num"), bitwise_and_Number},
    {operator_k("|", "num", "num"), bitwise_or_Number},
    {operator_k("^", "num", "num"), bitwise_xor_Number},
    {operator_k("<<", "num", "num"), bitwise_lshift_Number},
    {operator_k(">>", "num", "num"), bitwise_rshift_Number},
    {operator_k("<", "num", "num"), less_Number},
    {operator_k(">", "num", "num"), greater_Number},
    {operator_k("<=", "num", "num"), less_equal_Number},
    {operator_k(">=", "num", "num"), greater_equal_Number},
    {operator_k("==", "num", "num"), equal_Number},
    {operator_k("!=", "num", "num"), not_equal_Number},
    {operator_k("&&", "num", "num"), Logical_and},
    {operator_k("||", "num", "num"), Logical_or},
    {operator_k("&&", "str", "str"), Logical_and},
    {operator_k("||", "str", "str"), Logical_or},
    {operator_k("&&", "num", "str"), Logical_and},
    {operator_k("||", "num", "str"), Logical_or},
    {operator_k("&&", "str", "num"), Logical_and},
    {operator_k("||", "str", "num"), Logical_or},
};


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
    operator_k key(op, v1.getType(), v2.getType());
    if (operations.find(key) != operations.end()) {
        return operations[key](v1, v2);
    }
    throw runtime_error("Operation " + op + " not supported for " + v1.getType() + " and " + v2.getType());
}

/**
 * input / output Variable
 * "Zyad" : str
 * 5 : num
 * 5.5 : num
 * 5 + 5: 10 num
 * "Zyad" + "Hany" : "ZyadHany"
 * "Zyad" + 5 : "Zyad5"
 * n=5 : new variable n with value 5
 */
Variable::Variable(const string &expresion){
    *this = Variable("temp", "str", expresion);
}
