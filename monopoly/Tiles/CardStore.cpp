#include "CardStore.hpp"
#include "Bank.hpp"
#include "Error.hpp"
#include "InputManager.hpp"
#include "SingletonManager.hpp"
#include <iomanip>
#include <iostream>

CardStore* CardStore::instance = nullptr;

CardStore::CardStore(const GameConfig& config) {
    throw NotImplement("`CardStore::CardStore` not implement");
}

CardStore* CardStore::getInstance(const GameConfig& config) {
    throw NotImplement("`CardStore::getInstance` not implement");
    return nullptr;
}

CardStore* CardStore::getInstance() {
    throw NotImplement("`CardStore::getInstance` not implement");
    return nullptr;
}

void CardStore::destroyInstance() {
    throw NotImplement("`CardStore::destroyInstance` not implement");
}

void CardStore::displayStore(std::shared_ptr<Player> player) {
    throw NotImplement("`CardStore::displayStore` not implement");
}

void CardStore::purchaseCard(std::shared_ptr<Player> player, std::shared_ptr<Card> card) {
    throw NotImplement("`CardStore::purchaseCard` not implement");
}

std::vector<std::shared_ptr<Card>> CardStore::getCards() const {
    throw NotImplement("`CardStore::getCards` not implement");
}

std::shared_ptr<Card> CardStore::getCardByName(const std::string& cardName) const {
    throw NotImplement("`CardStore::getCardByName` not implement");
}