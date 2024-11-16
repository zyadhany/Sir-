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

};


#endif // _VARIABLE_H
