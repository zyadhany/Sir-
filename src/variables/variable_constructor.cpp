#include "variable.h"

/**
 * check if the expresion is valid by checking if the barnaces are valid
 * @param expresion
 * @return
 */
bool IsValidBarnaces(string expresion)
{
    int barnaces = 0;
    bool opendouble = false;
    for (int i = 0; i < expresion.size(); i++)
    {
        if (expresion[i] == '\"' && expresion[i - 1] != '\\') opendouble = !opendouble;
        if (opendouble) continue;

        if (expresion[i] == '(')
        {
            barnaces++;
        }
        else if (expresion[i] == ')')
        {
            barnaces--;
        }
    }
    return barnaces == 0;
}

/**
 * check if string has valid number of double quotes
 * @param str string
 * @return bool
 */
bool check_double_quotes(string str) {
    bool check = false;
    for (int i = 0; i < str.size(); i++) {
        if(str[i] == '\\' && str[i + 1] == '\"' && check) i++;
        else if(str[i] == '\"') check = !check;
    }
    return !check;
}
/**
 * trim the spaces from the string
 * @param str
 * @return string
 */
string trim_spaces(const string &str) {
    string temp = "";
    bool check = false;
    for (int i = 0; i < str.size(); i++) {
        if (!check && str[i] == ' ') continue;
        temp += str[i];

        if(i && str[i] == '\"' && str[i - 1] == '\\' && check) continue;
        if(str[i] == '\"') check = !check;
    }

    return temp;
}

/**
 * check if the string is a valid number
 * @param str
 * @return bool
 */
bool is_valid_number(string str) {
    if(str.size() == 0) return false;
    if(str[0] == '0' && str.size() > 1) return false;
    for (int i = 0; i < str.size(); i++) {
        if(i == 0 && str[i] == '-') continue;
        if(str[i] < '0' || str[i] > '9') return false;
    }
    return true;
}

/**
 * check if the string is a valid variable
 * @param str
 * @return bool
 */
bool is_valid_variable_name(string str) {
    if(str.size() == 0) return false;
    if(str[0] >= '0' && str[0] <= '9') return false;
    for (int i = 0; i < str.size(); i++) {
        if(str[i] < '0' || str[i] > '9') {
            if(str[i] < 'a' || str[i] > 'z') {
                if(str[i] < 'A' || str[i] > 'Z') {
                    if(str[i] != '_') return false;
                }
            }
        }
    }
    return true;
}

bool check_oppration(string &str) {
    for (auto opp : OPPRATORS)
        if (str.find(opp.first) != string::npos) return true;
    return false;
}

bool valid_expression(string &str) {
    bool check = true;
    check &= IsValidBarnaces(str);
    check &= check_double_quotes(str);
    // check not start or end with oppration
    return check;
}

Variable::Variable(const string &expresion){
    string exp = trim_spaces(expresion);
    if (!valid_expression(exp)) {
        throw runtime_error("Invalid string");
    }
    
    string expresiontocheck = exp.substr(exp[0] == '-');
    if (!check_oppration(expresiontocheck))
    {
        if (exp.empty()) *this = Variable("temp", "str", "");
        else if (exp[0] == '\"' && exp[exp.size() - 1] == '\"') *this = Variable("temp", "str", exp.substr(1, exp.size() - 2));
        else if (is_valid_number(exp)) *this = Variable("temp", "num", exp);
        else if (is_valid_variable_name(exp)) *this = GetVariable(exp);
        else throw runtime_error("Invalid string");
        return;
    }

    vector<Variable> vars;
    vector<string> ops;

    int at = 0;
    for (int i = 0; i < exp.size() - 1; i++)
    {
        if (exp[i] == '(')
        {
            int barnaces = 1;
            i++;
            
            bool opendouble = false;

            while (barnaces)
            {
                if (exp[i] == '\"' && exp[i - 1] != '\\') opendouble = !opendouble;

                if (opendouble) {
                    i++;
                    continue;
                }
        
                if (exp[i] == '(')
                    barnaces++;
                else if (exp[i] == ')')
                    barnaces--;
                i++;
            }
            string temp = exp.substr(at + 1, i - at - 2);
            vars.push_back(Variable(temp));
            at = i;
            i--;
            continue;
        }
        if (exp[i] == '\"')
        {
            i++;
            while (exp[i] != '\"' || exp[i - 1] == '\\')
                i++;
            string temp = exp.substr(at, i - at + 1);
            vars.push_back(Variable(temp));
            at = i + 1;
            continue;
        }
        if (i == at && exp[i] == '-') continue;

        string nxopp = exp.substr(i, 2);
        if (OPPRATORS.find(nxopp) != OPPRATORS.end())
        {    
            vars.push_back(Variable(exp.substr(at, i - at)));
            ops.push_back(nxopp);
            at = i + 2;
            i++;
            continue;
        }

        nxopp = exp.substr(i, 1);
        if (OPPRATORS.find(nxopp) != OPPRATORS.end())
        {
            if (i != at) vars.push_back(Variable(exp.substr(at, i - at)));
            ops.push_back(nxopp);
            at = i + 1;
        } 
    }

    if (at < exp.size()) vars.push_back(Variable(exp.substr(at, exp.size() - at)));
    

    *this = execute(ops, vars);
}
