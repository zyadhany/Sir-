#include <bits/stdc++.h>

using namespace std;

void PushStringVector(vector<string> &vec, string &str) {
    if (str != "") vec.push_back(str);
    str = "";
}

vector<string> parseLine(const string &line) {
    vector<string> tokens;
    string token = "";
    string endChar = " \t\n\r";
    bool gotDoubleQuote = false;

    for (char c : line) {
        bool isend = false; 
        
        if (endChar.find(c) != string::npos) isend = true;
        
        if (c == '"' || c == '\'') {
            if (gotDoubleQuote) isend = true;
            gotDoubleQuote = !gotDoubleQuote;
            PushStringVector(tokens, token);
        } else if (isend && !gotDoubleQuote) {
            PushStringVector(tokens, token);
        }
        else token += c;
    }
    if (token != "") tokens.push_back(token);

    return tokens;
}

void interpret(const string &line) {
    vector<string> tokens = parseLine(line);

    for (string token : tokens) {
        cout << token << endl;
    }
}

int main(int argc, char *argv[]) {
    string line;

    while (getline(cin, line)) {
        interpret(line);
    }
}