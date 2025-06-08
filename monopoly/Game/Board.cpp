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
    mapSize = config.getMapSize();
    tileWidth = config.getTileWidth();
    animation = config.getAnimation();
    animationTime = static_cast<int>(config.getAnimationTime());
    propertyLevelIcons = config.getPropertyLevelIcons();

    // setting tiles for board
    auto tileconfigs = config.getBoardTiles();
    for (const auto& tileconfig: tileconfigs){
        tiles.push_back(std::make_shared<Tile>(tileconfig.id, tileconfig.name));
    }
}

void Board::init(const GameConfig& config, const std::vector<std::shared_ptr<Player>>& players) {
    playersList = players;
    updatePlayerPositions(players);
    updateProperty(players);    
}

Board* Board::getInstance(const GameConfig& config) {
    if (!instance){
        instance = new Board(config);
    }
    return instance;
}

Board* Board::getInstance() {
    return instance;
}

void Board::destroyInstance() {
    if (instance){
        delete instance;
        instance = nullptr;
    }
}

int Board::getSize() const {
    return static_cast<int>(tiles.size());
}

std::shared_ptr<Tile> Board::getTile(int index) {
    if (index < 0 || index>= static_cast<int>(tiles.size())) return nullptr;
    return tiles[index];
}

std::vector<std::shared_ptr<Tile>> Board::getTileList() {
    return tiles;
}

void Board::drawBoard() {
    throw NotImplement("`Board::drawBoard` not implement");
}

void Board::drawMonopolyAscii() {
    throw NotImplement("`Board::drawMonopolyAscii` not implement");
}

void Board::updatePlayerPositions(const std::vector<std::shared_ptr<Player>>& players) {
    playersPosition.clear();
    for (const auto& player: players){
        playersPosition[player] = player->getPosition();
    }
}

std::vector<std::shared_ptr<PropertyTile>> Board::getPlayerProperty(const std::shared_ptr<Player>& player) {
    std::vector<std::shared_ptr<PropertyTile>> result;
    for (const auto& tile: tiles){
        auto prop = std::dynamic_pointer_cast<PropertyTile>(tile);
        if (prop && prop->getOwner() == player){
            result.push_back(prop);
        }
    }
    return result;
}

void Board::updateProperty(const std::vector<std::shared_ptr<Player>>& players) {
    propertyLevelBoard.clear();
    propertyLevelBoard.resize(mapSize, std::vector<int>(players.size(), 0));

    for (size_t i = 0; i < players.size(); i++){
        auto propertyTile = std::dynamic_pointer_cast<PropertyTile>(tiles[i]);
        if (propertyTile && propertyTile->getOwner()){
            auto owner = propertyTile->getOwner();
            auto it = std::find(players.begin(), players.end(), owner);
            if (it != players.end()){
                size_t playerIndex = std::distance(players.begin(), it);
                propertyLevelBoard[i][playerIndex] = propertyTile->getLevel();
            }
        }
    }
}

void Board::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    std::cout << "\033[2J\033[H"; // ANSI Escape Code to clear the screen and move the cursor to the top-left corner
#endif
}
