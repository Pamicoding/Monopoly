#include "MiniGameDialog.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QStackedWidget>
#include <QMessageBox>

// Placeholder widget class
class MiniGameWidget : public QWidget {
public:
    explicit MiniGameWidget(const QString& name, QWidget* parent = nullptr) : QWidget(parent) {
        QVBoxLayout* layout = new QVBoxLayout(this);
        QLabel* label = new QLabel(QString("🎮 This is %1 MiniGame").arg(name));
        label->setAlignment(Qt::AlignCenter);
        layout->addWidget(label);
        setLayout(layout);
    }
};

MiniGameDialog::MiniGameDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("🎲 Choose a MiniGame");
    setFixedSize(400, 300);
    setupUI();
}

void MiniGameDialog::setupUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    game1Button = new QPushButton("Game 1");
    game2Button = new QPushButton("Game 2");
    game3Button = new QPushButton("Game 3");

    buttonLayout->addWidget(game1Button);
    buttonLayout->addWidget(game2Button);
    buttonLayout->addWidget(game3Button);

    mainLayout->addLayout(buttonLayout);

    contentArea = new QStackedWidget();
    contentArea->addWidget(new MiniGameWidget("Game 1"));
    contentArea->addWidget(new MiniGameWidget("Game 2"));
    contentArea->addWidget(new MiniGameWidget("Game 3"));

    mainLayout->addWidget(contentArea);

    connect(game1Button, &QPushButton::clicked, this, [this]() {
        switchToGame("Game 1");
    });
    connect(game2Button, &QPushButton::clicked, this, [this]() {
        switchToGame("Game 2");
    });
    connect(game3Button, &QPushButton::clicked, this, [this]() {
        switchToGame("Game 3");
    });

    setLayout(mainLayout);
}

void MiniGameDialog::switchToGame(const QString& gameName) {
    if (gameName == "Game 1") {
        contentArea->setCurrentIndex(0);
    } else if (gameName == "Game 2") {
        contentArea->setCurrentIndex(1);
    } else if (gameName == "Game 3") {
        contentArea->setCurrentIndex(2);
    }
}