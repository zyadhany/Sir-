#include "command.h"

map<string, Variable (*)(Command &)> BLOCK_FUNCTIONS = {
    {"if", block_if},
    {"while", block_while},
    {"function", block_function},
    {"scope", block_scope}
};

Variable block_scope(Command &command) {
    return command.scope.runScope();
}

Variable block_if(Command &command) {
    Command condtionTrue("block", "scope", "");
    Command condtionFalse("block", "scope", "");
    condtionTrue.scope = command.scope;
    condtionFalse.scope = Scope(command.scope.line_block.second, command.scope.line_block.second);

    int cntif = 0;
    for (int i = command.scope.line_block.first; i < command.scope.line_block.second; i++) {
        Command cmd(COMMAND_LINES[i]);
        if (cmd.name == "if" || cmd.name == "while") {
            cntif++;
        } else if (COMMAND_LINES[i] == "else") {
            if (cntif == 0) {
                condtionTrue.scope.line_block.second = i;
                condtionFalse.scope.line_block.first = i + 1;
                break;
            }
        } else if (COMMAND_LINES[i] == "end") {
            cntif--;
        }
    }

    Variable cond(command.expression);
    if (!cond.isNull()) {
        return block_scope(condtionTrue);
    }
    if (command.name != "if") return Variable();
    return block_scope(condtionFalse);
}

Variable block_while(Command &command) {
    Variable ret;
    do {
        ret = block_if(command);
    } while (!ret.isNull() && ret.value != "6");
    
    return Variable();
}

Variable block_function(Command &command) {
    runtime_error("Not implemented");
    return Variable();
}

