#ifndef SIR_H

#include <bits/stdc++.h>
using namespace std;


void interpret(const string &line);

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

#endif // SIR_H
