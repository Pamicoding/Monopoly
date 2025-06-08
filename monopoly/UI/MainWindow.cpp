#include "MainWindow.hpp"
#include "CardDialog.hpp"
#include "MiniGameDialog.hpp"
#include "SudoDialog.hpp"
#include "Game.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

void MainWindow::refresh() {
    auto players = Game::getInstance()->getPlayers();

    std::vector<PlayerDisplayInfo> displayList;
    std::map<int, std::vector<QColor>> playerMap;
    std::map<int, QColor> ownershipMap;
    std::map<int, int> levelMap;

    for (const auto& p : players) {
        PlayerDisplayInfo info;
        info.name = QString::fromStdString(p->getName());
        info.color = QColor(QString::fromStdString(p->getColor()));
        info.rank = 1; // 排名邏輯要補上
        info.money = p->getMoney();
        info.status = p->isBankrupt() ? "BANKRUPT" : (p->isInHospital() ? "HOSPITAL" : "NORMAL");
        info.isCurrentTurn = p->checkIsMyTurn();
        displayList.push_back(info);

        playerMap[p->getPosition()].push_back(info.color);

        // 擁有的地產
        for (const auto& tile : Board::getInstance()->getPlayerProperty(p)) {
            ownershipMap[tile->getId()] = info.color;
            levelMap[tile->getId()] = tile->getLevel();
        }
    }

    playerPanel->setPlayerList(displayList);
    boardWidget->setPlayerMap(playerMap);
    boardWidget->setOwnershipMap(ownershipMap);
    boardWidget->setLevelMap(levelMap);
}

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setupUI();
}

void MainWindow::setupUI() {
    QWidget* central = new QWidget();
    QHBoxLayout* mainLayout = new QHBoxLayout(central);

    // 左側：地圖 + 玩家資訊
    boardWidget = new BoardWidget();
    playerPanel = new PlayerPanel();

    // 右側：功能按鈕
    QVBoxLayout* sidePanel = new QVBoxLayout();
    QPushButton* cardButton = new QPushButton("🃏 Cards");
    QPushButton* minigameButton = new QPushButton("🎲 MiniGame");
    QPushButton* sudoButton = new QPushButton("🛠️ Sudo");

    sidePanel->addWidget(cardButton);
    sidePanel->addWidget(minigameButton);
    sidePanel->addWidget(sudoButton);
    sidePanel->addStretch();

    mainLayout->addWidget(boardWidget);
    mainLayout->addWidget(playerPanel);
    mainLayout->addLayout(sidePanel);

    setCentralWidget(central);
    setWindowTitle("Monopoly Game");

    // 假資料：顯示卡片視窗測試用
    auto cards = GameConfig::getInstance().getCards();
    std::map<std::string, int> myCards = {
        {"Barrier Card", 2},
        {"Dice Card", 1},
        {"Bomb Card", 0}
    };

    connect(cardButton, &QPushButton::clicked, this, [=]() {
        auto* dialog = new CardDialog(this);
        dialog->setCards(cards, myCards);
        dialog->exec();
    });

    connect(minigameButton, &QPushButton::clicked, this, [=]() {
        auto* dialog = new MiniGameDialog(this);
        dialog->exec();
    });

    connect(sudoButton, &QPushButton::clicked, this, [=]() {
        auto* sudo = new SudoDialog(this);
        sudo->setExecutor([&](const ParsedCommand& cmd) {
            Game::getInstance()->executeSudoCommand(cmd);
            refresh();
        });
        sudo->exec();
    });
}
