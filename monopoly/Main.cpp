#include "Game/Game.hpp"
#include "Game/GameConfig.hpp"
#include "SingletonManager.hpp"
#include "UI/MainWindow.hpp"

#include <QApplication>
#include <QDebug>
#include <exception>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    try {
        GameMode mode = GameMode::DUEL;
        GameConfig &cfg = GameConfig::getInstance();
        cfg.setMode(mode);
        cfg.loadConfig();

        std::shared_ptr<Game> game = Game::getInstance(cfg);
        game->initGame();

        MainWindow window;
        window.refresh();
        window.show();
        int ret = app.exec();

        SingletonManager::destroyAll();
        return ret;
    } catch (const std::exception &e) {
        qWarning() << "Exception:" << e.what();
    }
    return 0;
}
