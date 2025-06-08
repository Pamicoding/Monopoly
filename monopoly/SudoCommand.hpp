#ifndef SUDOCOMMAND_HPP
#define SUDOCOMMAND_HPP

#include <string>
#include <vector>

enum class SudoCommandType {
    MOVE,
    GIVE,
    GET,
    ADDCARD,
    STATE,
    INFO,
    REFRESH,
    UNKNOWN
};
struct ParsedCommand {
    SudoCommandType type;
    std::vector<std::string> args;
};

struct CommandDefinition {
    std::string description;
    std::string usage;
    std::vector<std::string> examples;
    std::string prompt;
};
#endif  
