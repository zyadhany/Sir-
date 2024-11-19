#include "Sir.h"

void executeToken(vector<string> &tokens) {
    if (tokens.size() == 0) return;

    auto it = internal_functions.find(tokens[0]);
    if (it != internal_functions.end()) {
        Command command;
        command.type = "built-in";
        command.name = tokens[0];
        command.expression = tokens[1];
        command.runCommand();
    }
}
