#include "Player.hpp"
#include "Cards/Card.hpp"
#include "Error.hpp"
#include "InputManager.hpp"
#include "MiniGames/MiniGameManager.hpp"
#include <iomanip>
#include <iostream>
Player::Player(const std::string& n, const std::string& i, const std::string& c, long long m)
    : name(n)
    , icon(i)
    , color(c)
    , money(m)
    , position(0)
    , bankrupt(false)
    , inHospital(false)
    , isMyTurn(false)
    , hospitalRoundLeft(0)
    , diceControl(0) {}

std::string Player::getName() const {
    return name;
}

std::string Player::getIcon() const {
    return icon;
}

std::string Player::getColor() const {
    return color;
}

std::string Player::getIconWithColor() const {
    std::string iconWithColor = color + icon + "\033[0m";
    return iconWithColor;
}

std::string Player::getDisplayName() const {
    return getIconWithColor() + " " + getName();
}

long long Player::getMoney() const {
    return money;
}

int Player::getPosition() const {
    return position;
}

bool Player::isBankrupt() const {
    return bankrupt;
}

bool Player::isInHospital() const {
    return inHospital;
}

bool Player::checkIsMyTurn() const {
    return isMyTurn;
}

void Player::setPosition(int pos) {
    position = pos;
}

void Player::setMyTurn(bool b) {
    isMyTurn = b;
}

/**
 * Adds a specified amount to the player's balance.
 *
 * @param amount The amount of money to be added.
 *               For example, if amount = 100, then the player's balance will be increased by 100 (balance + amount).
 * @return Returns true if the addition is successful; returns false if the amount is negative
 */
bool Player::addMoney(long long amount) {
    throw NotImplement("`Player::addMoney` not implement");
}

/**
 * Deducts a specified amount from the player's balance.
 *
 * @param amount The amount of money to be deducted.
 *               For example, if amount = 100, then the player's balance will be reduced by 100 (balance - amount).
 * @return Returns true if the deduction is successful;
 *         returns false if the player's balance is insufficient or if the amount is negative
 */
bool Player::deductMoney(long long amount) {
    throw NotImplement("`Player::deductMoney` not implement");
}

void Player::setBankrupt(bool b) {
    throw NotImplement("`Player::setBankrupt` not implement");
}

void Player::sendToStart() {
    throw NotImplement("`Player::sendToStart` not implement");
}

void Player::sendToHospital(int rounds) {
    throw NotImplement("`Player::sendToHospital` not implement");
}

void Player::recoverFromHospital() {
    throw NotImplement("`Player::recoverFromHospital` not implement");
}

void Player::updateHospitalStatus() {
    throw NotImplement("`Player::updateHospitalStatus` not implement");
}

void Player::addCard(std::shared_ptr<Card> card) {
    throw NotImplement("`Player::addCard` not implement");
}

void Player::startMiniGame() {
    MiniGameManager::startMiniGame(shared_from_this());
}
void Player::endMiniGame() {
    MiniGameManager::endMiniGame(shared_from_this());
}

std::vector<std::shared_ptr<Card>> Player::getCards() {
    throw NotImplement("`Player::getCards` not implement");
}

void Player::displayCards(std::vector<std::shared_ptr<Player>>& players) {
    throw NotImplement("`Player::displayCards` not implement");
}

void Player::useCard(int index, std::vector<std::shared_ptr<Player>>& players) {
    throw NotImplement("`Player::useCard` not implement");
}

void Player::setDiceControl(int step) {
    throw NotImplement("`Player::setDiceControl` not implement");
}

int Player::getDiceControl() const {
    throw NotImplement("`Player::getDiceControl` not implement");
}

int Player::rollDice() {
    throw NotImplement("`Player::rollDice` not implement");
}
