#include "CardDialog.hpp"
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>
#include <QGraphicsOpacityEffect>

CardDialog::CardDialog(QWidget* parent)
    : QDialog(parent) {
    setWindowTitle("Your Cards");
    setFixedSize(600, 400);
    setupUI();
}

void CardDialog::setupUI() {
    QVBoxLayout* layout = new QVBoxLayout(this);
    cardLayout = new QGridLayout();
    layout->addLayout(cardLayout);
    setLayout(layout);
}

void CardDialog::setCards(const std::vector<CardConfig>& allCards, const std::map<std::string, int>& ownedCards) {
    updateCardDisplay(allCards, ownedCards);
}

void CardDialog::updateCardDisplay(const std::vector<CardConfig>& cards, const std::map<std::string, int>& owned) {
    // 清空原本卡片畫面
    QLayoutItem* child;
    while ((child = cardLayout->takeAt(0)) != nullptr) {
        if (QWidget* widget = child->widget()) {
            widget->deleteLater();
        }
        delete child;
    }

    const int col = 4; // 每行最多 4 張
    int row = 0, colIdx = 0;

    for (const auto& card : cards) {
        QString iconText = QString::fromStdString(card.icon);
        QString nameText = QString::fromStdString(card.name);
        int count = owned.count(card.name) ? owned.at(card.name) : 0;

        // icon label
        QLabel* iconLabel = new QLabel(iconText);
        iconLabel->setAlignment(Qt::AlignCenter);
        iconLabel->setFixedSize(80, 80);
        iconLabel->setStyleSheet("font-size: 24px; border: 1px solid gray; border-radius: 8px;");

        if (count == 0) {
            QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect;
            effect->setOpacity(0.4);
            iconLabel->setGraphicsEffect(effect);
        }

        // count label
        QLabel* countLabel = new QLabel(QString("x%1").arg(count));
        countLabel->setAlignment(Qt::AlignCenter);
        countLabel->setStyleSheet("font-size: 14px; color: gray;");

        QVBoxLayout* cardBox = new QVBoxLayout();
        cardBox->addWidget(iconLabel);
        cardBox->addWidget(countLabel);

        QWidget* cardWidget = new QWidget();
        cardWidget->setLayout(cardBox);
        cardLayout->addWidget(cardWidget, row, colIdx);

        if (++colIdx == col) {
            colIdx = 0;
            ++row;
        }
    }
}
