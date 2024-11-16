#include "variable.h"

Variable getStrVariable(const string &str) {
    return Variable("temp", "str", str);
}

Variable add_String(const Variable &v1, const Variable &v2) {
    if (v1.getType() != "str") throw runtime_error("v1 is not a string");
    if (v2.getType() != "str") throw runtime_error("v2 is not a string");

    return getStrVariable(v1.getValue() + v2.getValue());
}

Variable sub_String(const Variable &v1, const Variable &v2) {
    if (v1.getType() != "str") throw runtime_error("v1 is not a string");
    if (v2.getType() != "str") throw runtime_error("v2 is not a string");

    string res = v1.getValue();
    size_t found = res.find(v2.getValue());
    if (found != string::npos) {
        res.erase(found, v2.getValue().size());
    }

    return getStrVariable(res);
}

Variable mul_str_num(const Variable &v1, const Variable &v2) {
    if (v1.getType() != "str") throw runtime_error("v1 is not a string");
    if (v2.getType() != "num") throw runtime_error("v2 is not a number");

    string res;
    string str = v1.getValue();
    long long n = stoll(v2.getValue());
    for (int i = 0; i < n; i++) {
        res += str;
    }

    return getStrVariable(res);
}

Variable mul_num_str(const Variable &v1, const Variable &v2) {
    return mul_str_num(v2, v1);
}
