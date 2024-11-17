#ifndef SIR_H
#define SIR_H

#include <bits/stdc++.h>
#include "commands/command.h"
#include "variables/variable.h"

using namespace std;


class Scope {
public:
    pair<int, int> line_block;
    vector<Variable> scope_variables;

    Scope() {
        line_block = {0, 0};
    }

    void runScope();
    void addVariable(const Variable &var);
    void closeScope();

    ~Scope() {
        closeScope();
    }
};

/** Interpting **/
void interpret(const string &line);

/** executing **/
void executeToken(vector<string> &tokens);

/** opprations  **/
// bool IsValidOperation(string expresion);
// double MakeOperation(string expresion); 

/** Parsing **/
vector<string> parseCommandLine(const string &line);

#endif // SIR_H
