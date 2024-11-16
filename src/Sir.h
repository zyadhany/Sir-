#ifndef SIR_H

#include <bits/stdc++.h>
#include "variables/variable.h"

using namespace std;


struct BlockCode {
    vector<string> code;
};

struct IF_COND{
    string condtion;
    BlockCode block;
};

struct WHILE_LOOP{
    string condtion;
    BlockCode block;
};

struct FUNCTION{
    string name;
    vector<string> args;
    BlockCode block;
};

/** Interpting **/
void interpret(const string &line);

/** executing **/
void executeToken(vector<string> &tokens);

/** opprations  **/
double MakeOperation(string expresion); 

/** Parsing **/
vector<string> parseCommandLine(const string &line);

#endif // SIR_H
