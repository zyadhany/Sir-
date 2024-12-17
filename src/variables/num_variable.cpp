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

    if (res == "-0")
        res = "0";
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



Variable div_Number(const Variable &v1, const Variable &v2) {
    if (v1.getType() != "num") throw runtime_error("v1 is not a number");
    if (v2.getType() != "num") throw runtime_error("v2 is not a number");

    string res;
    string num1 = v1.getValue();
    string num2 = v2.getValue();

    if (num2 == "0") throw runtime_error("Division by zero");

    if (greater_Number(v2, v1).getValue() == "1") {
        res = "0";
    }
    else if (num1 == num2) {
        res = "1";
    }
    else {
        string quotient = "";
        string temp = "";

        int n = num1.size();
        for (int i = 0; i < n; ++i) {
            temp += num1[i];

            temp = removeLeadingZeros(temp);
            if (temp.empty()) temp = "0";

            int count = 0;
            Variable te("te", "num", temp);

            while (greater_equal_Number(te, v2).getValue() == "1") {
                temp = sub_String(temp, num2);
                te = Variable("te", "num", temp);
                count++;
            }

            quotient += (count + '0');
        }

        res = removeLeadingZeros(quotient);
        if (res.empty()) res = "0";
    }

    return getNumVariable(res);
}


Variable mod_Number(const Variable &v1, const Variable &v2) {
    if (v1.getType() != "num") throw runtime_error("v1 is not a number");
    if (v2.getType() != "num") throw runtime_error("v2 is not a number");

    string num1 = v1.getValue();
    string num2 = v2.getValue();

    if (num2 == "0") throw runtime_error("Modulo by zero");

    if (greater_Number(v2, v1).getValue() == "1") {
        return getNumVariable(num1);
    }

    if (num1 == num2) {
        return getNumVariable("0");
    }

    string temp = "";
    string remainder = "";

    int n = num1.size();
    for (int i = 0; i < n; ++i) {
        temp += num1[i];

        temp = removeLeadingZeros(temp);
        if (temp.empty()) temp = "0";

        int count = 0;
        Variable te("te", "num", temp);

        while (greater_equal_Number(te, v2).getValue() == "1") {
            temp = sub_String(temp, num2);
            te = Variable("te", "num", temp);
            count++;
        }
    }

    remainder = removeLeadingZeros(temp);
    if (remainder.empty()) remainder = "0";

    return getNumVariable(remainder);
}


string NumStringToBinery(string num) {
    string res = "";
    bool isvalue = 1;
    int ptr = 0;

    while(ptr < num.size())
    {
        int lst = num[num.size() - 1] - '0';
        num[num.size() - 1] = (lst / 2) + '0';
        res += (lst % 2) + '0';

        for (int j = num.size() - 2; j >= ptr; j--)
        {
            int at = num[j] - '0';
            num[j] = (at / 2) + '0';
            int nxt = num[j + 1] - '0' + 5 * (at % 2);

            if (nxt >= 10) {
                num[j]++;
                num[j + 1] = nxt % 10 + '0';
            } else {
                num[j + 1] = nxt + '0';
            }
        }
        while (ptr < num.size() && num[ptr] == '0') ptr++;
    }

    reverse(res.begin(), res.end());
    return res;
}

string multiplyByPowerOf2(const string& num, int power) {
    string result = num;
    for (int i = 0; i < power; ++i) {
        int carry = 0;
        for (int j = result.size() - 1; j >= 0; --j) {
            int digit = (result[j] - '0') * 2 + carry;
            result[j] = (digit % 10) + '0';
            carry = digit / 10;
        }
        if (carry > 0) {
            result.insert(result.begin(), carry + '0');
        }
    }
    return result;
}

string binaryToDecimalHelper(const string& bin, int start, int end) {
    if (start == end) {
        return bin[start] == '1' ? "1" : "0";
    }
    int mid = (start + end) / 2;
    string left = binaryToDecimalHelper(bin, start, mid);
    string right = binaryToDecimalHelper(bin, mid + 1, end);

    int power = end - mid;
    string leftShifted = multiplyByPowerOf2(left, power);
    string result = leftShifted;

    int carry = 0;
    int i = leftShifted.size() - 1, j = right.size() - 1;
    while (i >= 0 || j >= 0 || carry > 0) {
        int leftDigit = (i >= 0) ? (result[i] - '0') : 0;
        int rightDigit = (j >= 0) ? (right[j] - '0') : 0;
        int sum = leftDigit + rightDigit + carry;
        if (i >= 0) {
            result[i] = (sum % 10) + '0';
        } else {
            result.insert(result.begin(), (sum % 10) + '0');
        }
        carry = sum / 10;
        --i;
        --j;
    }

    return result;
}

string BineryToNumString(const string& bin) {
    return binaryToDecimalHelper(bin, 0, bin.size() - 1);
}


Variable bitwise_and_Number(const Variable &v1, const Variable &v2) {
    if (v1.getType() != "num") throw runtime_error("v1 is not a number");
    if (v2.getType() != "num") throw runtime_error("v2 is not a number");

    string res;
    string num1 = v1.getValue();
    string num2 = v2.getValue();

    string num1bin = NumStringToBinery(num1);
    string num2bin = NumStringToBinery(num2);
    reverse(num1bin.begin(), num1bin.end());
    reverse(num2bin.begin(), num2bin.end());
    while (num1bin.size() < num2bin.size())
        num1bin += '0';

    while (num2bin.size() < num1bin.size())
        num2bin += '0';

    reverse(num1bin.begin(), num1bin.end());
    reverse(num2bin.begin(), num2bin.end());

    for (int i = 0; i < num1bin.size(); ++i) {
        res += '0';
        if (num1bin[i] == '1' && num2bin[i] == '1')
            res[i] = '1';
        else
            res[i] = '0';
    }
    cout<<res<<endl;
    res = BineryToNumString(res);
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
