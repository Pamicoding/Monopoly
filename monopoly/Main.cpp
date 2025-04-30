#include "Game/Game.hpp"
#include "Game/GameConfig.hpp"
#include "SingletonManager.hpp"
#include <exception>
#include <iostream>

using namespace std;
int main() {
    try {
        GameMode mode = GameMode::DUEL;
        GameConfig::getInstance().setMode(mode);
        ios::sync_with_stdio(false);
        cin.tie(nullptr);

        // Game game(GameConfig::getInstance());
        std::shared_ptr<Game> game = Game::getInstance(GameConfig::getInstance());
        game->initGame();
        game->start();

        // End of the game
        SingletonManager::destroyAll(); // Destroy all singleton instances
    } catch (NotImplement& e) {
        std::cout << e.what() << '\n';
    }
    return 0;
}
