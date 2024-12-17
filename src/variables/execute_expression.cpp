#include "variable.h"

/**
 * execute the expression and return the result
 * @param operations vector<string> operations
 * @param vars vector<Variable> vars
 * @return Variable
 */
Variable execute(vector<string> operations, vector<Variable> vars) {
    if (operations.size() == 0) return vars[0];
    if (operations.size() == 1) return MakeOperation(vars[0], vars[1], operations[0]);
    vector<vector<string>> priority = {
        {"*", "/", "%"},
        {"+", "-"},
        {"<<", ">>"},
        {"<", ">", "<=", ">="},
        {"==", "!="},
        {"&"},
        {"^"},
        {"|"},
        {"&&"},
        {"||"}
    };

    for (auto &p : priority) {
        int i = 0;
        while (i < operations.size()) {
            if (find(p.begin(), p.end(), operations[i]) != p.end()) {
                vars[i] = MakeOperation(vars[i], vars[i + 1], operations[i]);
                vars.erase(vars.begin() + i + 1, vars.begin() + i + 2);
                operations.erase(operations.begin() + i, operations.begin() + i + 1);
            } else {
                i++;
            }
        }
    }
    return vars[0];
}
