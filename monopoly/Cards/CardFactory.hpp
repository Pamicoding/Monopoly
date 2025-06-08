// CardFactory.hpp
#ifndef CARD_FACTORY_HPP
#define CARD_FACTORY_HPP

#include <memory>
#include <random>
#include "Card.hpp"
// #include "DestroyCard.hpp"

class CardFactory {
public:
    static std::shared_ptr<Card> getRandomCard() {
        std::random_device rd;
        std::mt19937 gen(rd()); // 隨機數生成器
        std::uniform_int_distribution<> dis(0, 0); // TODO: 擴展範圍以包含更多卡片類型

        int r = dis(gen); // 生成隨機數
        switch (r) {
            // case 0: return std::make_shared<DestroyCard>();
            default: return nullptr;
        }
    }
};

#endif // CARD_FACTORY_HPP