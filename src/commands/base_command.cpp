#include "../Sir.h"

class Base_Command {
    public:
        Base_Command(vector<string> args) {
            this->args = args;
        }

        ~Base_Command() {
            cout << "Base_Command destructor" << endl;
        }

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
    private:
        vector<string> args;
};