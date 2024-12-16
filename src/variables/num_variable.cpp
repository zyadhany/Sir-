#include "variable.h"

Variable getNumVariable(string num) {
    return Variable("temp", "num", num);
}

string removeLeadingZeros(const string& num) {
    size_t pos = num.find_first_not_of('0');
    if (pos == string::npos) return "0"; // If all characters are '0'
    return num.substr(pos);
}

bool isNegative(const string& num) {
    return !num.empty() && num[0] == '-';
}

string removeSign(const string& num) {
    if (isNegative(num)) {
        return num.substr(1);
    }
    return num;
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

// subtract 2 numbers as string and return the result
string sub_String(const string &num1, const string &num2) {
    string a = num1, b = num2;
    if (a == b) return "0";

    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    string result = "";
    int borrow = 0;

    for (int i = 0; i < a.size(); i++) {
        int digitA = a[i] - '0';
        int digitB = (i < b.size() ? b[i] - '0' : 0);
        int diff = digitA - digitB - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result += diff + '0';
    }

    reverse(result.begin(), result.end());
    result = removeLeadingZeros(result);
    return result;
}

Variable greater_Number(const Variable &v1, const Variable &v2) {
    if (v1.getType() != "num") throw runtime_error("v1 is not a number");
    if (v2.getType() != "num") throw runtime_error("v2 is not a number");

    string res = "0";
    string num1 = v1.getValue();
    string num2 = v2.getValue();
    if(num1.size() > num2.size()){
        res = "1";
    } else if(num1.size() < num2.size()){
        res = "0";
    } else {
        for(int i = 0; i < num1.size(); i++){
            if(num1[i] > num2[i]){
                res = "1";
                break;
            } else if(num1[i] < num2[i]){
                res = "0";
                break;
            }
        }
    }
    return getNumVariable(res);
}

Variable less_Number(const Variable &v1, const Variable &v2) {
    return greater_Number(v2, v1);
}

Variable greater_equal_Number(const Variable &v1, const Variable &v2) {
    if (v1.getType() != "num") throw runtime_error("v1 is not a number");
    if (v2.getType() != "num") throw runtime_error("v2 is not a number");

    string res = "1";
    string num1 = v1.getValue();
    string num2 = v2.getValue();
    if(num1.size() > num2.size()){
        res = "1";
    } else if(num1.size() < num2.size()){
        res = "0";
    } else {
        for(int i = 0; i < num1.size(); i++){
            if(num1[i] > num2[i]){
                res = "1";
                break;
            } else if(num1[i] < num2[i]){
                res = "0";
                break;
            }
        }
    }
    return getNumVariable(res);
}

Variable less_equal_Number(const Variable &v1, const Variable &v2) {
    return greater_equal_Number(v2, v1);
}

Variable equal_Number(const Variable &v1, const Variable &v2) {
    return greater_equal_Number(v1, v2) * greater_equal_Number(v2, v1);
}

Variable not_equal_Number(const Variable &v1, const Variable &v2) {
    return greater_Number(v1, v2) + greater_Number(v2, v1);
}


Variable add_Number(const Variable &v1, const Variable &v2) {
    if (v1.getType() != "num") throw runtime_error("v1 is not a number");
    if (v2.getType() != "num") throw runtime_error("v2 is not a number");

    string res;
    string num1 = v1.getValue();
    string num2 = v2.getValue();
    if (isNegative(num1) && isNegative(num2))
    {
        num1 = removeSign(num1);
        num2 = removeSign(num2);
        res = '-' + add_String(num1, num2);
    }
    else if (isNegative(num1))
    {
        num1 = removeSign(num1);
        if (greater_equal_Number(v2, v1).getValue() == "1")
            res = sub_String(num2, num1);
        else
            res = '-' + sub_String(num1, num2);
    }
    else if (isNegative(num2))
    {
        num2 = removeSign(num2);
        if (greater_equal_Number(v1, v2).getValue() == "1")
            res = sub_String(num1, num2);
        else
            res = '-' + sub_String(num2, num1);
    }
    else
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
    if (isNegative(num1) && isNegative(num2))
    {
        num1 = removeSign(num1);
        num2 = removeSign(num2);
        res = mul_String(num1, num2);
    }
    else if (isNegative(num1) || isNegative(num2))
    {
        num1 = removeSign(num1);
        num2 = removeSign(num2);
        res = '-' + mul_String(num1, num2);
    }
    else
        res = mul_String(num1, num2);

    return getNumVariable(res);
}

Variable sub_Number(const Variable &v1, const Variable &v2) {
    if (v1.getType() != "num") throw runtime_error("v1 is not a number");
    if (v2.getType() != "num") throw runtime_error("v2 is not a number");
    string res;
    string num1 = v1.getValue();
    string num2 = v2.getValue();
    if (isNegative(num2))
    {
        num2 = removeSign(num2);
        if (isNegative(num1))
        {
            num1 = removeSign(num1);
            if (greater_equal_Number(v2, v1).getValue() == "1")
                res = sub_String(num2, num1);
            else
                res = '-' + sub_String(num1, num2);
        }
        else
        {
            res = add_String(num1, num2);
        }
    }
    else
    {
        if (isNegative(num1))
        {
            num1 = removeSign(num1);
            res = '-' + add_String(num1, num2);
        }
        else
        {
            if (greater_equal_Number(v1, v2).getValue() == "1")
                res = sub_String(num1, num2);
            else
                res = '-' + sub_String(num2, num1);
        }
    }

    return getNumVariable(res);
}

// here
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

Variable bitwise_and_Number(const Variable &v1, const Variable &v2) {
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

Variable bitwise_or_Number(const Variable &v1, const Variable &v2) {
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

Variable bitwise_xor_Number(const Variable &v1, const Variable &v2) {
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

Variable bitwise_lshift_Number(const Variable &v1, const Variable &v2) {
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

Variable bitwise_rshift_Number(const Variable &v1, const Variable &v2) {
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

Variable Logical_and(const Variable &v1, const Variable &v2) {
    bool res = (!(v1.isNull()) && !(v2.isNull()));
    return getNumVariable(res ? "1" : "0");
}

Variable Logical_or(const Variable &v1, const Variable &v2) {
    bool res = ((!v1.isNull()) || !(v2.isNull()));
    return getNumVariable(res ? "1" : "0");
}
