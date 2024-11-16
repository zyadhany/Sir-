#include "variable.h"

Variable getStrVariable(const string &str) {
    return Variable("temp", "str", str);
}

Variable add_String(const Variable &v1, const Variable &v2) {
    if (v1.getType() != "str") throw runtime_error("v1 is not a string");
    if (v2.getType() != "str") throw runtime_error("v2 is not a string");

    return getStrVariable(v1.getValue() + v2.getValue());
}
