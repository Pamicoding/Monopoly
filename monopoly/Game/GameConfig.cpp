#include "GameConfig.hpp"
#include "Error.hpp"
#include "nlohmann/json.hpp"
#include <exception>
#include <fstream>
#include <iostream>
#include <stdexcept>

// Initialize the unique `GameConfig` instance
GameConfig GameConfig::instance;

GameConfig& GameConfig::getInstance() {
    return instance;
}

void GameConfig::loadConfig() {
    std::ifstream file("resources/config.json");
    if (!file) {
        throw std::runtime_error("Failed to open config.json");
    }

    nlohmann::json j;
    file >> j;

    // Load game mode settings (assume always DEBUG first)
    const auto& debug = j["modes"]["DEBUG"];
    setPlayersNum(debug.value("playersNum", 2));
    setPlayersName(debug["playersName"].get<std::vector<std::string>>());
    setStartMoney(debug.value("startMoney", 0));
    setWinMoney(debug.value("winMoney", 0));
    setPassingStartBonus(debug.value("passingStartBonus", 0));

    // Load global icon & style config
    playerIcons = j.value("playerIcons", std::vector<std::string>());
    playerColors = j.value("playerColors", std::vector<std::string>());
    propertyLevelIcons = j.value("propertyLevelIcons", std::vector<std::string>());
    tileWidth = j.value("tileWidth", 14);
    animation = j.value("animation", false);
    animationTime = j.value("animationTime", 0LL);

    // Load board tiles
    std::vector<TileConfig> tiles;
    for (const auto& tile : j["boardTiles"]) {
        TileConfig t;
        t.id = tile.value("index", 0);
        t.name = tile.value("name", "");
        t.type = tile.value("type", "");
        t.cost = tile.value("price", 0);
        t.rent = tile.value("toll", 0);
        tiles.push_back(t);
    }
    setBoardTiles(tiles);

    // Load cards
    std::vector<CardConfig> cardList;
    for (const auto& card : j["cards"]) {
        CardConfig c;
        c.name = card.value("name", "");
        c.icon = card.value("icon", "");
        c.price = card.value("price", 0);
        c.effect = card.value("effect", "");
        cardList.push_back(c);
    }
    setCards(cardList);

    // Optional: event ranges
    std::map<std::string, std::pair<int, int>> rangeMap;
    for (auto& [key, val] : j["eventValueRange"].items()) {
        int min = val[0];
        int max = val[1];
        rangeMap[key] = {min, max};
    }
    setEventValueRange(rangeMap);

}

void GameConfig::setMode(GameMode newMode) {
    mode = newMode;
}

GameMode GameConfig::getMode() const {
    return mode;
}

void GameConfig::setPlayersNum(int num) {
    playersNum = num;
}

int GameConfig::getPlayersNum() const {
    return playersNum;
}

void GameConfig::setPlayersName(const std::vector<std::string>& names) {
    playersName = names;
}

std::vector<std::string> GameConfig::getPlayerNames() const {
    return playersName;
}

void GameConfig::setPlayerIcons(const std::vector<std::string>& icons) {
    playerIcons = icons;
}

std::vector<std::string> GameConfig::getPlayerIcons() const {
    return playerIcons;
}

void GameConfig::setPlayerColors(const std::vector<std::string>& icons) {
    playerColors = icons;
}

std::vector<std::string> GameConfig::getPlayerColors() const {
    return playerColors;
}

void GameConfig::setPropertyLevelIcons(const std::vector<std::string>& icons) {
    propertyLevelIcons = icons;
}

std::vector<std::string> GameConfig::getPropertyLevelIcons() const {
    return propertyLevelIcons;
}

std::map<int, std::string> GameConfig::getLocationMap() const {
    return locationMap;
}

void GameConfig::setStartMoney(int amount) {
    startMoney = amount; 
}

int GameConfig::getStartMoney() const {
    return startMoney;
}

void GameConfig::setWinMoney(int amount) {
    winMoney = amount;
}

int GameConfig::getWinMoney() const {
    return winMoney;
}

void GameConfig::setPassingStartBonus(int amount) {
    passingStartBonus = amount;
}

int GameConfig::getPassingStartBonus() const {
    return passingStartBonus;
}

void GameConfig::setBoardTiles(const std::vector<TileConfig>& tiles) {
    boardTiles = tiles;
}

std::vector<TileConfig> GameConfig::getBoardTiles() const {
    return boardTiles;
}

void GameConfig::setCards(const std::vector<CardConfig>& cards) {
    this->cards = cards;
}

std::vector<CardConfig> GameConfig::getCards() const {
    return cards;
}

void GameConfig::setEventValueRange(const std::map<std::string, std::pair<int, int>>& range) {
    eventValueRange = range;
}

std::map<std::string, std::pair<int, int>> GameConfig::getEventValueRange() const {
    return eventValueRange;
}

void GameConfig::setAnimation(bool status) {
    animation = status;
}

bool GameConfig::getAnimation() const {
    return animation;
}

int GameConfig::getMapSize() const {
    return mapSize;
}

int GameConfig::getTileWidth() const {
    return static_cast<int>(tileWidth);
}

long long GameConfig::getAnimationTime() const {
    return animationTime;
}
