#ifndef SUDOCOMMANDPARSER_HPP
#define SUDOCOMMANDPARSER_HPP

#include "SudoCommand.hpp"
#include <string>
#include <map>
#include <vector>
#include <nlohmann/json.hpp>

class SudoCommandParser {
public:
    SudoCommandParser();

    // 解析輸入指令字串，回傳解析後的 ParsedCommand 結構
    ParsedCommand parse(const std::string& input) const;

    // 取得指定指令的定義資料（for usage / prompt 顯示）
    CommandDefinition getDefinition(const std::string& commandName) const;

    // 取得所有支援指令（for auto complete / 下拉選單）
    std::vector<std::string> getSupportedCommands() const;

private:
    std::map<std::string, CommandDefinition> commandMap;

    void loadFromJson(); // 載入 command.json
    SudoCommandType mapToType(const std::string& cmd) const;
};

#endif // SUDOCOMMANDPARSER_HPP
