#include "command.h"

map<string, Variable (*)(Command &)> BLOCK_FUNCTIONS = {
    {"if", block_if},
    {"while", block_while},
    {"function", block_function},
    {"scope", block_scope}
};

Variable block_scope(Command &command) {
    command;
    command.scope;
    command.scope.scope_variables;
    command.scope.runScope();
    return Variable();
}

Variable block_if(Command &command) {
    runtime_error("Not implemented");
    return Variable();
}

Variable block_while(Command &command) {
    runtime_error("Not implemented");
    return Variable();
}

Variable block_function(Command &command) {
    runtime_error("Not implemented");
    return Variable();
}

