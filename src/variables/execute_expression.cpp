#include "variable.h"

/**
 * execute the expression and return the result
 * @param ops vector<string> ops
 * @param vars vector<Variable> vars
 * @return Variable
 */
Variable execute(vector<string> ops, vector<Variable> vars) {
    if (ops.size() == 0) return vars[0];
    if (ops.size() == 1) return MakeOperation(vars[0], vars[1], ops[0]);
    
    int sz = 0;
    for (auto opp : OPPRATORS) sz = max(sz, opp.second);
    vector<vector<string>> priority(sz + 1);
    for (auto opp : OPPRATORS) priority[opp.second].push_back(opp.first);

    for (auto &p : priority) {
        int i = 0;
        while (i < ops.size()) {
            if (find(p.begin(), p.end(), ops[i]) != p.end()) {
                vars[i] = MakeOperation(vars[i], vars[i + 1], ops[i]);
                vars.erase(vars.begin() + i + 1, vars.begin() + i + 2);
                ops.erase(ops.begin() + i, ops.begin() + i + 1);
            } else {
                i++;
            }
        }
    }
    return vars[0];
}
