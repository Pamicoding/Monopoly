#include "Game.hpp"
#include "Error.hpp"
#include "InputManager.hpp"
#include "MiniGames/MiniGameManager.hpp"
#include "Utils/Utils.hpp"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <unordered_map>

std::default_random_engine Game::engine;
std::shared_ptr<Game> Game::instance = nullptr;

Game::Game(const GameConfig& cfg)
    : config(cfg)
    , currentState(State::INIT)
    , gameForceControl(false) {
    throw NotImplement("`Game::Game` not implement");
}

std::shared_ptr<Game> Game::getInstance(const GameConfig& config) {
    throw NotImplement("`Game::getInstance`not implement");
}

void Game::initGame() {
    throw NotImplement("`Game::initGame` not implement");
}

void Game::start() {
    throw NotImplement("`Game::start` not implement");
}

void Game::processPlayerAction(std::shared_ptr<Player> player, std::shared_ptr<Tile> tile, bool isCommandResult) {
    throw NotImplement("`Game::processPlayerAction` not implement");
}

bool Game::processCommand(std::shared_ptr<Player> player, const std::string& input) {
    throw NotImplement("`Game::processCommand` not implement");
}

void Game::throwDice(std::shared_ptr<Player> player) {
    throw NotImplement("`Game::throwDice` not implement");
}

void Game::checkGameOver() {
    throw NotImplement("`Game::checkGameOver` not implement");
}

void Game::endGame() {
    throw NotImplement("`Game::endGame` not implement");
}

void Game::changeState(State newState) {
    throw NotImplement("`Game::changeState` not implement");
}

State& operator++(State& state) {
    throw NotImplement("not implement");
}

void Game::setState(const std::string& state) {
    throw NotImplement("`Game::setState` not implement");
}

const nlohmann::json& Game::playerAction() {
    throw NotImplement("`Game::playerAction` not implement");
}

const nlohmann::json& Game::playerAction(const std::string& key) {
    throw NotImplement("`Game::playerAction` not implement");
}

void Game::movePlayer(std::shared_ptr<Player> player, int steps) {
    throw NotImplement("`Game::movePlayer` not implement");
}

std::string Game::getStateString() {
    throw NotImplement("`Game::getStateString` not implement");
}

bool Game::isActivateState() const {
    throw NotImplement("`Game::isActivateState` not implement");
}

bool Game::isRoundState() const {
    throw NotImplement("`Game::isRoundState` not implement");
}