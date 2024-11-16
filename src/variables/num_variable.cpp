#include "variable.h"

Variable getNumVariable(string num) {
    return Variable("temp", "num", num);
}

// add 2 numbers as string and return the result 
string add_String(const string &num1, const string &num2) {
    string res;
    int carry = 0;
    int i = num1.size() - 1;
    int j = num2.size() - 1;

    while (i >= 0 || j >= 0) {
        int n1 = i >= 0 ? num1[i] - '0' : 0;
        int n2 = j >= 0 ? num2[j] - '0' : 0;

        int sum = n1 + n2 + carry;
        carry = sum / 10;
        sum = sum % 10;

        res.push_back(sum + '0');

        i--;
        j--;
    }

    if (carry) {
        res.push_back(carry + '0');
    }

    reverse(res.begin(), res.end());

    return res;
}
    

Variable add_Number(const Variable &v1, const Variable &v2) {
    if (v1.getType() != "num") throw runtime_error("v1 is not a number");
    if (v2.getType() != "num") throw runtime_error("v2 is not a number");

    string res;
    string num1 = v1.getValue();
    string num2 = v2.getValue();


    return getNumVariable(res);
}
