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

/** Str Variables **/
Variable add_String(const Variable &v1, const Variable &v2);

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
        if (this->type != var.type) {
            throw runtime_error("Cannot add " + var.type + " to " + this->type);
        }

        if (this->type == "num") {
            return add_Number(*this, var);
        } else if (this->type == "str") {
            return add_String(*this, var);
        }

        throw runtime_error("Cannot add " + this->type + " to " + var.type);
    }

    Variable operator-(const Variable &var) {
        if (this->type != var.type) {
            throw runtime_error("Cannot subtract " + var.type + " from " + this->type);
        }

        if (this->type == "num") {
            return sub_Number(*this, var);
        }
    }

    Variable operator*(const Variable &var) {
        if (this->type != var.type) {
            throw runtime_error("Cannot multiply " + var.type + " with " + this->type);
        }

        if (this->type == "num") {
            return mul_Number(*this, var);
        }
    }

    Variable operator/(const Variable &var) {
        if (this->type != var.type) {
            throw runtime_error("Cannot divide " + var.type + " by " + this->type);
        }

        if (this->type == "num") {
            return div_Number(*this, var);
        }
    }
};


#endif // _VARIABLE_H
