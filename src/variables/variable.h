#ifndef _VARIABLE_H
#define _VARIABLE_H

#include <bits/stdc++.h>
#include <typeinfo>
using namespace std;

class Variable;

extern vector<Variable> variables;
Variable ConvertToVariable(const string &expresion);
Variable GetVariable(string name);
Variable SetVariable(Variable var);


/** Num Variables **/
Variable add_Number(const Variable &v1, const Variable &v2);
Variable sub_Number(const Variable &v1, const Variable &v2);
Variable mul_Number(const Variable &v1, const Variable &v2);
Variable div_Number(const Variable &v1, const Variable &v2);
Variable mod_Number(const Variable &v1, const Variable &v2);
Variable bitwise_and_Number(const Variable &v1, const Variable &v2);
Variable bitwise_or_Number(const Variable &v1, const Variable &v2);
Variable bitwise_xor_Number(const Variable &v1, const Variable &v2);
Variable bitwise_lshift_Number(const Variable &v1, const Variable &v2);
Variable bitwise_rshift_Number(const Variable &v1, const Variable &v2);
Variable greater_Number(const Variable &v1, const Variable &v2);
Variable less_Number(const Variable &v1, const Variable &v2);
Variable greater_equal_Number(const Variable &v1, const Variable &v2);
Variable less_equal_Number(const Variable &v1, const Variable &v2);
Variable equal_Number(const Variable &v1, const Variable &v2);
Variable not_equal_Number(const Variable &v1, const Variable &v2);
Variable and_operator(const Variable &v1, const Variable &v2);


/** Str Variables **/
Variable add_String(const Variable &v1, const Variable &v2);
Variable sub_String(const Variable &v1, const Variable &v2);
Variable mul_str_num(const Variable &v1, const Variable &v2);
Variable mul_num_str(const Variable &v1, const Variable &v2);

/** Operator **/
struct operator_k
{
    string op;
    string type1;
    string type2;

    operator_k(const string &op, const string &type1, const string &type2)
        : op(op), type1(type1), type2(type2) {}

    bool operator<(const operator_k &other) const
    {
        if (op != other.op)
            return op < other.op;
        if (type1 != other.type1)
            return type1 < other.type1;
        return type2 < other.type2;
    }
};
extern map<operator_k, Variable (*)(const Variable&, const Variable&)> operations;
Variable MakeOperation(const Variable &v1, const Variable &v2, const string &op);


class Variable{
private:
    string name;
    string type;
    string value;
    //vector<Variable> params;
    //vector<map<string, string>> methods;
public:

    Variable(const string& name, const string& type, const string& value="")
        : name(name), type(type), value(value) {}
    virtual ~Variable() = default;

    void setValue(const string &newValue) {
        if (validateValue(newValue)) {
            value = newValue;
        } else {
            throw runtime_error("Invalid value for " + type + " " + name + ": " + newValue);
        }
    }

    bool validateValue(const string& newValue) {
        // todo: implement validation for each type
        return true;
    }

    string getValue() const {
        return value;
    }

    string getName() const {
        return name;
    }

    string getType() const {
        return type;
    }

    void print() const {
        cout << name << " " << type << " " << value << endl;
    }

    Variable getCopy() const {
        return Variable(name, type, value);
    }
    
    Variable& operator=(const Variable &var) {
        if (this->type != var.type) {
            throw runtime_error("Cannot assign " + var.type + " to " + this->type);
        }
        this->value = var.value;
        return *this;
    }

    Variable operator+(const Variable &var) {
        return MakeOperation(*this, var, "+");
    }

    Variable operator-(const Variable &var) {
        return MakeOperation(*this, var, "-");
    }

    Variable operator*(const Variable &var) {
        return MakeOperation(*this, var, "*");
    }

    Variable operator/(const Variable &var) {
        return MakeOperation(*this, var, "/");
    }

    Variable operator%(const Variable &var) {
        return MakeOperation(*this, var, "%");
    }

    Variable operator&(const Variable &var) {
        return MakeOperation(*this, var, "&");
    }

    Variable operator|(const Variable &var) {
        return MakeOperation(*this, var, "|");
    }

    Variable operator^(const Variable &var) {
        return MakeOperation(*this, var, "^");
    }

    Variable operator<<(const Variable &var) {
        return MakeOperation(*this, var, "<<");
    }

    Variable operator>>(const Variable &var) {
        return MakeOperation(*this, var, ">>");
    }

    Variable operator+=(const Variable &var) {
        return *this = *this + var;
    }

    Variable operator-=(const Variable &var) {
        return *this = *this - var;
    }

    Variable operator*=(const Variable &var) {
        return *this = *this * var;
    }

    Variable operator/=(const Variable &var) {
        return *this = *this / var;
    }

    Variable operator%=(const Variable &var) {
        return *this = *this % var;
    }

    Variable operator&=(const Variable &var) {
        return *this = *this & var;
    }

    Variable operator|=(const Variable &var) {
        return *this = *this | var;
    }

    Variable operator^=(const Variable &var) {
        return *this = *this ^ var;
    }

    Variable operator<<=(const Variable &var) {
        return *this = *this << var;
    }

    Variable operator>>=(const Variable &var) {
        return *this = *this >> var;
    }

    Variable operator<(const Variable &var) {
        return MakeOperation(*this, var, "<");
    }

    Variable operator>(const Variable &var) {
        return MakeOperation(*this, var, ">");
    }

    Variable operator<=(const Variable &var) {
        return MakeOperation(*this, var, "<=");
    }

    Variable operator>=(const Variable &var) {
        return MakeOperation(*this, var, ">=");
    }

    Variable operator==(const Variable &var) {
        return MakeOperation(*this, var, "==");
    }

    Variable operator!=(const Variable &var) {
        return MakeOperation(*this, var, "!=");
    }

    Variable operator&&(const Variable &var) {
        return MakeOperation(*this, var, "&&");
    }

    Variable operator||(const Variable &var) {
        return MakeOperation(*this, var, "||");
    }

    Variable operator!() {
        return MakeOperation(*this, *this, "!");
    }

    Variable operator~() {
        return MakeOperation(*this, *this, "~");
    }
    


};


#endif // _VARIABLE_H
