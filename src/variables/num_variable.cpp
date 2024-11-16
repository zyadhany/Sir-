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
    res = add_String(num1, num2);
    return getNumVariable(res);
}

// multiply 2 numbers as string and return the result
string mul_String(const string &num1, const string &num2) {
    string res(num1.size() + num2.size(), '0');
    for (int i = num1.size() - 1; i >= 0; i--) {
        for (int j = num2.size() - 1; j >= 0; j--) {
            int mul = (num1[i] - '0') * (num2[j] - '0');
            int sum = mul + (res[i + j + 1] - '0');
            res[i + j + 1] = sum % 10 + '0';
            res[i + j] += sum / 10;
        }
    }

    size_t startpos = res.find_first_not_of('0');
    if (string::npos != startpos) {
        return res.substr(startpos);
    }
    return "0";
}

Variable mul_Number(const Variable &v1, const Variable &v2) {
    if (v1.getType() != "num") throw runtime_error("v1 is not a number");
    if (v2.getType() != "num") throw runtime_error("v2 is not a number");

    string res;
    string num1 = v1.getValue();
    string num2 = v2.getValue();
    if(num1[0] == '-' && num2[0] == '-'){
        num1.erase(0, 1);
        num2.erase(0, 1);
    } else if(num1[0] == '-'){
        num1.erase(0, 1);
        res.push_back('-');
    } else if(num2[0] == '-'){
        num2.erase(0, 1);
        res.push_back('-');
    }
    res += mul_String(num1, num2);

    return getNumVariable(res);
}

// subtract 2 numbers as string and return the result
string sub_String(const string &num1, const string &num2) {
    string res;
    int borrow = 0;
    int i = num1.size() - 1;
    int j = num2.size() - 1;

    while (i >= 0 || j >= 0) {
        int n1 = i >= 0 ? num1[i] - '0' : 0;
        int n2 = j >= 0 ? num2[j] - '0' : 0;

        int sub = n1 - n2 - borrow;
        if (sub < 0) {
            sub += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        res.push_back(sub + '0');

        i--;
        j--;
    }

    reverse(res.begin(), res.end());

    return res;
}

Variable sub_Number(const Variable &v1, const Variable &v2) {
    if (v1.getType() != "num") throw runtime_error("v1 is not a number");
    if (v2.getType() != "num") throw runtime_error("v2 is not a number");

    string res;
    string num1 = v1.getValue();
    string num2 = v2.getValue();
    long long n1 = stoll(num1);
    long long n2 = stoll(num2);
    long long sub = n1 - n2;
    res = to_string(sub);

    return getNumVariable(res);
}

Variable div_Number(const Variable &v1, const Variable &v2) {
    if (v1.getType() != "num") throw runtime_error("v1 is not a number");
    if (v2.getType() != "num") throw runtime_error("v2 is not a number");

    string res;
    string num1 = v1.getValue();
    string num2 = v2.getValue();
    long long n1 = stoll(num1);
    long long n2 = stoll(num2);
    if (n2 == 0) throw runtime_error("Division by zero");
    long long div = n1 / n2;
    res = to_string(div);

    return getNumVariable(res);
}

Variable mod_Number(const Variable &v1, const Variable &v2) {
    if (v1.getType() != "num") throw runtime_error("v1 is not a number");
    if (v2.getType() != "num") throw runtime_error("v2 is not a number");

    string res;
    string num1 = v1.getValue();
    string num2 = v2.getValue();
    long long n1 = stoll(num1);
    long long n2 = stoll(num2);
    if (n2 == 0) throw runtime_error("Division by zero");
    long long mod = n1 % n2;
    res = to_string(mod);

    return getNumVariable(res);
}

Variable and_Number(const Variable &v1, const Variable &v2) {
    if (v1.getType() != "num") throw runtime_error("v1 is not a number");
    if (v2.getType() != "num") throw runtime_error("v2 is not a number");

    string res;
    string num1 = v1.getValue();
    string num2 = v2.getValue();
    long long n1 = stoll(num1);
    long long n2 = stoll(num2);
    long long and_res = n1 & n2;
    res = to_string(and_res);

    return getNumVariable(res);
}

Variable or_Number(const Variable &v1, const Variable &v2) {
    if (v1.getType() != "num") throw runtime_error("v1 is not a number");
    if (v2.getType() != "num") throw runtime_error("v2 is not a number");

    string res;
    string num1 = v1.getValue();
    string num2 = v2.getValue();
    long long n1 = stoll(num1);
    long long n2 = stoll(num2);
    long long or_res = n1 | n2;
    res = to_string(or_res);

    return getNumVariable(res);
}

Variable xor_Number(const Variable &v1, const Variable &v2) {
    if (v1.getType() != "num") throw runtime_error("v1 is not a number");
    if (v2.getType() != "num") throw runtime_error("v2 is not a number");

    string res;
    string num1 = v1.getValue();
    string num2 = v2.getValue();
    long long n1 = stoll(num1);
    long long n2 = stoll(num2);
    long long xor_res = n1 ^ n2;
    res = to_string(xor_res);

    return getNumVariable(res);
}

Variable lshift_Number(const Variable &v1, const Variable &v2) {
    if (v1.getType() != "num") throw runtime_error("v1 is not a number");
    if (v2.getType() != "num") throw runtime_error("v2 is not a number");

    string res;
    string num1 = v1.getValue();
    string num2 = v2.getValue();
    long long n1 = stoll(num1);
    long long n2 = stoll(num2);
    long long lshift_res = n1 << n2;
    res = to_string(lshift_res);

    return getNumVariable(res);
}

Variable rshift_Number(const Variable &v1, const Variable &v2) {
    if (v1.getType() != "num") throw runtime_error("v1 is not a number");
    if (v2.getType() != "num") throw runtime_error("v2 is not a number");

    string res;
    string num1 = v1.getValue();
    string num2 = v2.getValue();
    long long n1 = stoll(num1);
    long long n2 = stoll(num2);
    long long rshift_res = n1 >> n2;
    res = to_string(rshift_res);

    return getNumVariable(res);
}
