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
    throw NotImplement("`GameConfig::loadConfig` not implement");
}

void GameConfig::setMode(GameMode newMode) {
    throw NotImplement("`GameConfig::setMode` not implement");
}

GameMode GameConfig::getMode() const {
    throw NotImplement("`GameConfig::getMode` not implement");
}

void GameConfig::setPlayersNum(int num) {
    throw NotImplement("`GameConfig::setPlayersNum` not implement");
}

int GameConfig::getPlayersNum() const {
    throw NotImplement("`GameConfig::getPlayersNum` not implement");
}

void GameConfig::setPlayersName(const std::vector<std::string>& names) {
    throw NotImplement("`GameConfig::setPlayersName` not implement");
}

std::vector<std::string> GameConfig::getPlayerNames() const {
    throw NotImplement("`GameConfig::getPlayerNames` not implement");
}

void GameConfig::setPlayerIcons(const std::vector<std::string>& icons) {
    throw NotImplement("`GameConfig::setPlayerIcons` not implement");
}

std::vector<std::string> GameConfig::getPlayerIcons() const {
    throw NotImplement("`GameConfig::getPlayerIcons` not implement");
}

void GameConfig::setPlayerColors(const std::vector<std::string>& icons) {
    throw NotImplement("`GameConfig::setPlayerColors` not implement");
}

std::vector<std::string> GameConfig::getPlayerColors() const {
    throw NotImplement("`GameConfig::getPlayerColors` not implement");
}

void GameConfig::setPropertyLevelIcons(const std::vector<std::string>& icons) {
    throw NotImplement("`GameConfig::setPropertyLevelIcons` not implement");
}

std::vector<std::string> GameConfig::getPropertyLevelIcons() const {
    throw NotImplement("`GameConfig::getPropertyLevelIcons` not implement");
}

std::map<int, std::string> GameConfig::getLocationMap() const {
    throw NotImplement("`GameConfig::getLocationMap` not implement");
}

void GameConfig::setStartMoney(int amount) {
    throw NotImplement("`GameConfig::setStartMoney` not implement");
}

int GameConfig::getStartMoney() const {
    throw NotImplement("`GameConfig::getStartMoney` not implement");
}

void GameConfig::setWinMoney(int amount) {
    throw NotImplement("`GameConfig::setWinMoney` not implement");
}

int GameConfig::getWinMoney() const {
    throw NotImplement("`GameConfig::getWinMoney` not implement");
}

void GameConfig::setPassingStartBonus(int amount) {
    throw NotImplement("`GameConfig::setPassingStartBonus` not implement");
}

int GameConfig::getPassingStartBonus() const {
    throw NotImplement("`GameConfig::getPassingStartBonus` not implement");
}

void GameConfig::setBoardTiles(const std::vector<TileConfig>& tiles) {
    throw NotImplement("`GameConfig::setBoardTiles` not implement");
}

std::vector<TileConfig> GameConfig::getBoardTiles() const {
    throw NotImplement("`GameConfig::getBoardTiles` not implement");
}

void GameConfig::setCards(const std::vector<CardConfig>& cards) {
    throw NotImplement("`GameConfig::setCards` not implement");
}

std::vector<CardConfig> GameConfig::getCards() const {
    throw NotImplement("`GameConfig::getCards` not implement");
}

void GameConfig::setEventValueRange(const std::map<std::string, std::pair<int, int>>& range) {
    throw NotImplement("`GameConfig::setEventValueRange` not implement");
}

std::map<std::string, std::pair<int, int>> GameConfig::getEventValueRange() const {
    throw NotImplement("`GameConfig::getEventValueRange` not implement");
}

void GameConfig::setAnimation(bool status) {
    throw NotImplement("`GameConfig::setAnimation` not implement");
}

bool GameConfig::getAnimation() const {
    throw NotImplement("`GameConfig::getAnimation()` not implement");
}

int GameConfig::getMapSize() const {
    throw NotImplement("`GameConfig::getMapSize()` not implement");
}

int GameConfig::getTileWidth() const {
    throw NotImplement("`GameConfig::getTileWidth()` not implement");
}

long long GameConfig::getAnimationTime() const {
    throw NotImplement("`GameConfig::getAnimationTime()` not implement");
}
