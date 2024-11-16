#ifndef BASE_COMMAND_H
#define BASE_COMMAND_H

#include <bits/stdc++.h>
#include "../variables/variable.h"

using namespace std;

class Base_Command {
    protected:
        vector<string> args;
    
    public:
        Base_Command(vector<string> args) {
            this->args = args;
        }
        ~Base_Command() = default;

        void run() {
            cout << "Base_Command run" << endl;
        }

        string getStringExpression(int start=1, int end=-1) {
            if (end == -1) {
                end = this->args.size();
            }

            string value = "";
            for (int i = start; i < end; i++) {
                value += this->args[i];
            }
            return value;
        }

        string getValueOfArg(int start=1, int end=-1) {
            string expression = getStringExpression(start, end);

            return expression;
        }
};

#endif
