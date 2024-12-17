#ifndef SIR_H
#define SIR_H

#include <bits/stdc++.h>
#include "commands/command.h"
#include "variables/variable.h"

using namespace std;

struct SirGlobal
{
    int line;

    SirGlobal()
    {
        line = 0;
    }
};
extern SirGlobal sirGlobal;

/** Interpting **/
void interpret(const string &line);

/** executing **/
void executeToken(vector<string> &tokens);

/** opprations  **/
// bool IsValidOperation(string expresion);
// double MakeOperation(string expresion); 

/** Parsing **/
vector<string> parseCommandLine(const string &line);
vector<string> readfile(const string &filename);
string parseline(string line);

#endif // SIR_H
