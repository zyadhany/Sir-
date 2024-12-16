#include "variable.h"

/**
 * check if the expresion is valid by checking if the barnaces are valid
 * @param expresion
 * @return
 */
vector<string> operations = {"+", "-", "*", "/", "%", "&", "|", "^", "<<", ">>", "<", ">", "<=", ">=", "==", "!=", "&&", "||", "!", "~"};
bool IsValidBarnaces(string expresion)
{
    int barnaces = 0;
    for (int i = 0; i < expresion.size(); i++)
    {
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
string trim_spaces(string &str) {
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

 * Variable()

    Variable("(n + 20) * m");
    Variabele("n") + 



    Variable("n") + Va
 */
Variable::Variable(const string &expresion){
    string exp = trim_spaces(expresion);
    bool check = false;
    for (auto opp : operations) {
        if (exp.find(opp) != string::npos) {
            check = true;
            break;
        }
    }
    if (!check)
    {
        *this = Variable("temp", "str", exp);
        return;

    }
    if (!IsValidBarnaces(exp))
        throw runtime_error("Invalid barnaces");
    
    
    // *this = Variable("temp", "str", exp);
}


