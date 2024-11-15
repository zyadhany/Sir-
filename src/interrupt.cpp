#include "Sir.h"


void interpret(const string &line) {
    vector<string> tokens = parseCommandLine(line);
    
    if (tokens.size() == 0) return;

    executeToken(tokens);    
}

