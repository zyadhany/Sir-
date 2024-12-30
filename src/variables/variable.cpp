#include "variable.h"

map<string, Variable> variables;

map<string, int> OPPRATORS = {
    {"*", 2}, {"/", 2}, {"%", 2},
    {"+", 3}, {"-", 3},
    {"<<", 4}, {">>", 4},
    {"<", 5}, {">", 5}, {"<=", 5}, {">=", 5},
    {"==", 6}, {"!=", 6},
    {"&", 7},
    {"^", 8},
    {"|", 9},
    {"&&", 10},
    {"||", 11},
    {"=", 12}
};

map<operator_k, Variable (*)(const Variable&, const Variable&)> TYPEOPRATOR = {
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
    {operator_k("==", "str", "str"), equal_String},
    {operator_k("!=", "num", "num"), not_equal_Number},
    {operator_k("&&", "num", "num"), Logical_and},
    {operator_k("||", "num", "num"), Logical_or},
    {operator_k("&&", "str", "str"), Logical_and},
    {operator_k("||", "str", "str"), Logical_or},
    {operator_k("&&", "num", "str"), Logical_and},
    {operator_k("||", "num", "str"), Logical_or},
    {operator_k("&&", "str", "num"), Logical_and},
    {operator_k("||", "str", "num"), Logical_or}
};

Variable GetVariable(string name){
    int index = -1;
    if (variables.find(name) != variables.end()) {
        return variables[name];
    }

    // throw runtime_error("Variable " + name + " not found");
    return Variable(name, "null", "");
}

Variable SetVariable(Variable var){
    variables[var.getName()] = var;
    return var;
}

Variable MakeOperation(const Variable &v1, const Variable &v2, const string &op) {
    if (op == "=") {
        Variable temp = v2;
        if (v1.name == "null") throw runtime_error("invalid assignment");
        temp.name = v1.name;
        return SetVariable(temp);
    }

    operator_k key(op, v1.getType(), v2.getType());
    if (TYPEOPRATOR.find(key) != TYPEOPRATOR.end()) {
        return TYPEOPRATOR[key](v1, v2);
    }
    throw runtime_error("Operation " + op + " not supported for " + v1.getType() + " and " + v2.getType());
}
