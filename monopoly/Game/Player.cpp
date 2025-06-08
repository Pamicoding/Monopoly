#include "Player.hpp"
#include "Cards/Card.hpp"
#include "Error.hpp"
#include "InputManager.hpp"
#include "MiniGames/MiniGameManager.hpp"
#include <iomanip>
#include <iostream>
#include <random>
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
    if (bankrupt) return false;
    money += amount;
    return true;
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
    if (bankrupt) return false;
    money -= amount;
    if (money < 0){
        bankrupt = true;
        money = 0;
        Game::log("[PLAYER] " + name + " is bankrupt!");
    }
    return true;
}

void Player::setBankrupt(bool b) {
    bankrupt = b;
    if (b) money = 0;
}

void Player::sendToStart() {
    position = 0;
    Game::log("[PLAYER] send to start");
}

void Player::sendToHospital(int rounds) {
    inHospital = true;
    hospitalRoundLeft = rounds;
    Game::log("[PLAYER-HOSPITAL] " + name + " is sent to hospital for " + std::to_string(rounds) + " rounds.");
}

void Player::recoverFromHospital() {
    inHospital = false;
    hospitalRoundLeft = 0;
    Game::log("[PLAYER-HOSPITAL] " + name + " has recovered and left the hospital.");
}

void Player::updateHospitalStatus() {
    if (!inHospital) return;

    if (hospitalRoundLeft > 0){
        hospitalRoundLeft--;
        Game::log("[PLAYER-HOSPITAL] " + name + " has " + std::to_string(hospitalRoundLeft) + " rounds left in hospital.");
    }

    if (hospitalRoundLeft <= 0){
        recoverFromHospital();
    }
}

void Player::addCard(std::shared_ptr<Card> card) {
    if (!card) return;
    cards.push_back(card);
}

void Player::startMiniGame() {
    MiniGameManager::startMiniGame(shared_from_this());
}
void Player::endMiniGame() {
    MiniGameManager::endMiniGame(shared_from_this());
}

std::map<std::string, int> Player::getCardCounts() const {
    std::map<std::string, int> cardCountMap;
    for (const auto& card : cards) {
        if (card) {
            cardCountMap[card->getName()]++;
        }
    }
    return cardCountMap;
}

std::vector<std::shared_ptr<Card>> Player::getCards() {
    return cards;
}

void Player::displayCards(std::vector<std::shared_ptr<Player>>& players) {
    for (size_t i = 0; i < cards.size(); i++){
        if (cards[i]){
            Game::log(std::to_string(i) + ". " + cards[i]->getName() + " - " + cards[i]->getEffect());
        }
    };
}

void Player::useCard(int index, std::vector<std::shared_ptr<Player>>& players) {
    if (index < 0 || index >= static_cast<int>(cards.size())){
        Game::log("[PLAYER-CARD] Invalid card index");
        return;
    };

    auto card = cards[index];
    if (!card) return;

    card->useEffect(players, shared_from_this());
    cards.erase(cards.begin()+index);

    Game::log("[PLAYER-CARD] Card used: " + card->getName());
}

void Player::setDiceControl(int step) {
    diceControl = step;
}

int Player::getDiceControl() const {
    return diceControl;
}

int Player::rollDice() {
    if (diceControl != -1){
        int result = diceControl;
        diceControl = -1;
        Game::log("[PLAYER-DICE] Controlled dice result: " + std::to_string(result));
        return result;
    }

    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dist(1, 6);

    int result = dist(gen);
    Game::log("[PLAYER-DICE] Random roll: " + std::to_string(result));
    return result;
}
