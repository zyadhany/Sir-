#include "command.h"

void Scope::runScope() {
    for (int i = line_block.first; i < line_block.second; i++) {
        Command command(COMMAND_LINES[i]);
        command.runCommand();
    }
}
