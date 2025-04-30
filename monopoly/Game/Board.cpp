#include "Board.hpp"
#include "Error.hpp"
#include "SingletonManager.hpp"
#include "Tiles/CardStore.hpp"
#include "Utils/Utils.hpp"
#include <iomanip>
#include <iostream>
#include <map>
#include <vector>
#ifdef _WIN32
#    include <windows.h> // For system("cls")
#endif

Board* Board::instance = nullptr;
std::string resetColor = "\033[0m";

Board::Board(const GameConfig& config) {
    throw NotImplement("`Board::Board` not implement");
}

void Board::init(const GameConfig& config, const std::vector<std::shared_ptr<Player>>& players) {
    throw NotImplement("`Board::init` not implement");
}

Board* Board::getInstance(const GameConfig& config) {
    throw NotImplement("`Board::getInstance` not implement");
}

Board* Board::getInstance() {
    throw NotImplement("`Board::getInstance` not implement");
}

void Board::destroyInstance() {
    throw NotImplement("`Board::destroyInstance` not implement");
}

int Board::getSize() const {
    throw NotImplement("`Board::getSize` not implement");
}

std::shared_ptr<Tile> Board::getTile(int index) {
    throw NotImplement("`Board::getTile` not implement");
}

std::vector<std::shared_ptr<Tile>> Board::getTileList() {
    throw NotImplement("`Board::getTileList` not implement");
}

void Board::drawBoard() {
    throw NotImplement("`Board::drawBoard` not implement");
}

void Board::drawMonopolyAscii() {
    throw NotImplement("`Board::drawMonopolyAscii` not implement");
}

void Board::updatePlayerPositions(const std::vector<std::shared_ptr<Player>>& players) {
    throw NotImplement("`Board::updatePlayerPositions` not implement");
}

std::vector<std::shared_ptr<PropertyTile>> Board::getPlayerProperty(const std::shared_ptr<Player>& player) {
    throw NotImplement("`Board::getPlayerProperty` not implement");
}

void Board::updateProperty(const std::vector<std::shared_ptr<Player>>& players) {
    throw NotImplement("`Board::updateProperty` not implement");
}

void Board::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    std::cout << "\033[2J\033[H"; // ANSI Escape Code to clear the screen and move the cursor to the top-left corner
#endif
}
