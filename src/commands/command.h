#ifndef BASE_COMMAND_H
#define BASE_COMMAND_H

#include <bits/stdc++.h>
#include "../variables/variable.h"

class Command;
extern map<string, Variable (*)(const Command &)> internal_functions;
extern vector<string> COMMAND_LINES;
extern map<string, Variable (*)(Command &)> BLOCK_FUNCTIONS;


/** built-in function **/
Variable builtin_print(const Command &command);
Variable builtin_var(const Command &command);

/** block function **/
Variable block_scope(Command &command);
Variable block_if(Command &command);
Variable block_while(Command &command);
Variable block_function(Command &command);


class Scope {
public:
    pair<int, int> line_block;
    vector<Variable> scope_variables;

    Scope(int start, int end) {
        line_block = {start, end};
    }

    Scope() {
        line_block = {-1, -1};
    }

    void runScope();
};

/**
 * @brief Command class
 * 
 * @types:
 * - expression: expression -> run expression (function, variable, opperation)
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
    Scope scope;
    string expression;

    Command(const string type, const string name, const string expression) {
        this->type = type;
        this->name = name;
        this->expression = expression;
    }

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
