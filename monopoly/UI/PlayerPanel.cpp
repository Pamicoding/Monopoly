#include "PlayerPanel.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QPixmap>
#include <QFrame>

PlayerPanel::PlayerPanel(QWidget* parent) : QWidget(parent) {
    setMinimumWidth(200);
}

void PlayerPanel::setPlayerList(const std::vector<PlayerDisplayInfo>& players) {
    currentPlayers = players;
    refreshLayout();
}

void PlayerPanel::refreshLayout() {
    // 清除原本 layout
    QLayout* oldLayout = layout();
    if (oldLayout) {
        QLayoutItem* item;
        while ((item = oldLayout->takeAt(0)) != nullptr) {
            if (QWidget* widget = item->widget()) {
                widget->deleteLater();
            }
            delete item;
        }
        delete oldLayout;
    }

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    for (const auto& p : currentPlayers) {
        // 每個玩家一個 group
        QGroupBox* box = new QGroupBox(QString("🎖️ Rank #%1").arg(p.rank));
        QVBoxLayout* v = new QVBoxLayout(box);

        // 名稱 + icon + 顏色圓形
        QHBoxLayout* nameLayout = new QHBoxLayout();
        QLabel* colorLabel = new QLabel();
        colorLabel->setFixedSize(12, 12);
        colorLabel->setStyleSheet(QString("background-color: %1; border-radius: 6px;")
                                  .arg(p.color.name()));
        QLabel* nameLabel = new QLabel(QString("🧑 %1").arg(p.name));
        nameLabel->setStyleSheet("font-weight: bold;");

        nameLayout->addWidget(colorLabel);
        nameLayout->addWidget(nameLabel);
        nameLayout->addStretch();

        // 金額
        QLabel* moneyLabel = new QLabel(QString("💰 $%1").arg(p.money));
        moneyLabel->setStyleSheet("color: darkgreen;");

        // 狀態
        QString stateText = p.status;
        if (p.isCurrentTurn)
            stateText += " 🔥 My Turn!";
        QLabel* statusLabel = new QLabel(QString("Status: %1").arg(stateText));

        v->addLayout(nameLayout);
        v->addWidget(moneyLabel);
        v->addWidget(statusLabel);
        box->setLayout(v);

        // 特殊樣式：當前玩家高亮
        if (p.isCurrentTurn) {
            box->setStyleSheet("border: 2px solid red;");
        }

        mainLayout->addWidget(box);
    }

    mainLayout->addStretch();
    setLayout(mainLayout);
}
