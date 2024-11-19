#ifndef BASE_COMMAND_H
#define BASE_COMMAND_H

#include <bits/stdc++.h>
#include "../variables/variable.h"

class Command;
extern map<string, Variable (*)(const Command &)> internal_functions;

/** built-in function **/
Variable builtin_print(const Command &command);

class Scope {
public:
    pair<int, int> line_block;
    vector<Variable> scope_variables;

    Scope() {
        line_block = {INT32_MAX, 0};
    }

    void runScope();
    void addVariable(const Variable &var);
    void closeScope();

    ~Scope() {
        closeScope();
    }
};

/**
 * @brief Command class
 * 
 * @types:
 * - expression: expression -> run expression (function, variable, opperation)
 * 
 * - variable: name = expression -> variable assignment
 * 
 * - built-in: name expression -> run expression depending on name
 *   - name: print, return, break, continue, exit, game.
 * 
 * - Block: name expression \\ code block \\ end
 *  - name: if, while, function.
 */
class Command {
public:
    string type;
    string name;
    // Scope scope;
    string expression;

    Command() {
        type = "null";
        name = "";
        expression = "";
    }
    Command(const string &line);
    Variable runCommand();
    Variable runExpression();
    Variable runBuiltIn();
    Variable runVariable();
    Variable runBlock();
};


#endif
