#include "Bank.hpp"
#include "Error.hpp"
#include "SingletonManager.hpp"
Bank* Bank::instance = nullptr;

Bank::Bank() {
    throw NotImplement("`Bank::Bank` not implement");
}

Bank* Bank::getInstance() {
    throw NotImplement("`Bank::getInstance` not implement");
    return nullptr;
}

void Bank::destroyInstance() {
    throw NotImplement("`Bank::destroyInstance` not implement");
}

void Bank::payToPlayer(std::shared_ptr<Player> player, long long amount) {
    throw NotImplement("`Bank::payToPlayer` not implement");
}
void Bank::receiveFromPlayer(std::shared_ptr<Player> player, long long amount) {
    throw NotImplement("`Bank::receiveFromPlayer` not implement");
}

long long Bank::getTotalMoneyInBank() const {
    throw NotImplement("`Bank::getTotalMoneyInBank` not implement");
}
