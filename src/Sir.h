#ifndef SIR_H
#define SIR_H

#include <bits/stdc++.h>
#include "commands/command.h"
#include "variables/variable.h"

using namespace std;


/** Interpting **/
void interpret(const string &line);

/** executing **/
void executeToken(vector<string> &tokens);

/** opprations  **/
// bool IsValidOperation(string expresion);
// double MakeOperation(string expresion); 

/** Parsing **/
vector<string> readfile(const string &filename);
string parseline(string line);

#endif // SIR_H
