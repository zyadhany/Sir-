#include "command.h"

Variable Scope::runScope() {
    for (int i = line_block.first; i < line_block.second; i++) {
        if (COMMAND_LINES[i] == "continue") return Variable("5");
        if (COMMAND_LINES[i] == "break") return Variable("6");
        Command command(COMMAND_LINES[i]);

        if (command.type == "block") {
            int cntblok = 0;

            for (int j = i + 1; j < line_block.second; j++) {
                Command cmd(COMMAND_LINES[j]);
                if (cmd.type == "block") {
                    cntblok++;
                } else if (COMMAND_LINES[j] == "end") {
                    if (cntblok == 0) {
                        command.scope = Scope(i + 1, j);
                        i = j;
                        break;
                    }
                    cntblok--;
                }
            }
        }

        string val = command.runCommand().value;
        if (command.type == "block" && (val == "5" || val == "6")) return Variable(val);
    }

    return Variable("1");
}
