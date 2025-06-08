#include "SudoCommandParser.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>

using json = nlohmann::json;

SudoCommandParser::SudoCommandParser() {
    loadFromJson();
}

void SudoCommandParser::loadFromJson() {
    std::ifstream file("resources/command.json"); // 確保這個路徑正確
    if (!file) {
        throw std::runtime_error("Failed to open command.json");
    }

    json j;
    file >> j;

    for (auto& [key, value] : j.items()) {
        CommandDefinition def;
        def.description = value.value("description", "");
        def.usage = value.value("usage", "");
        def.prompt = value.value("prompt", "");
        def.examples = value.value("examples", std::vector<std::string>{});
        commandMap[key] = def;
    }
}

SudoCommandType SudoCommandParser::mapToType(const std::string& cmd) const {
    if (cmd == "move") return SudoCommandType::MOVE;
    if (cmd == "give") return SudoCommandType::GIVE;
    if (cmd == "get") return SudoCommandType::GET;
    if (cmd == "addcard") return SudoCommandType::ADDCARD;
    if (cmd == "state") return SudoCommandType::STATE;
    if (cmd == "info") return SudoCommandType::INFO;
    return SudoCommandType::UNKNOWN;
}

ParsedCommand SudoCommandParser::parse(const std::string& input) const {
    std::istringstream iss(input);
    std::string token;
    std::vector<std::string> tokens;

    while (iss >> token) {
        tokens.push_back(token);
    }

    if (tokens.empty() || tokens[0][0] != '/') {
        return { SudoCommandType::UNKNOWN, {} };
    }

    std::string commandName = tokens[0].substr(1); // remove leading '/'
    SudoCommandType type = mapToType(commandName);
    tokens.erase(tokens.begin()); // remove command

    return { type, tokens };
}

CommandDefinition SudoCommandParser::getDefinition(const std::string& commandName) const {
    auto it = commandMap.find(commandName);
    if (it != commandMap.end()) {
        return it->second;
    }
    return {};
}

std::vector<std::string> SudoCommandParser::getSupportedCommands() const {
    std::vector<std::string> cmds;
    for (const auto& pair : commandMap) {
        cmds.push_back(pair.first);
    }
    return cmds;
}
