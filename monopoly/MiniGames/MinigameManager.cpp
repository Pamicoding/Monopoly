#include "MiniGameManager.hpp"
#include "Error.hpp"
#include "Game/Board.hpp"
#include "Game/Player.hpp"
#include <iostream>
#include <memory>

void MiniGameManager::startMiniGame(std::shared_ptr<Player> player) {
    throw NotImplement("`MiniGameManager::startMiniGame` not implement");
}

void MiniGameManager::endMiniGame(std::shared_ptr<Player> player) {
    throw NotImplement("`MiniGameManager::endMiniGame` not implement");
}

void MiniGameManager::listMiniGames() {
    throw NotImplement("`MiniGameManager::listMiniGames` not implement");
}

long long MiniGameManager::setBetAmount(std::shared_ptr<Player> player) {
    throw NotImplement("`MiniGameManager::setBetAmount` not implement");
}