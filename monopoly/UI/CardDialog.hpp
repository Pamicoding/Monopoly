#ifndef CARDDIALOG_HPP
#define CARDDIALOG_HPP

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QMap>
#include <QVector>
#include <QString>
#include <QGraphicsOpacityEffect>
#include "GameConfig.hpp"

class CardDialog : public QDialog {
    Q_OBJECT

public:
    explicit CardDialog(QWidget* parent = nullptr);

    // 傳入全卡片定義 + 擁有數量
    void setCards(const std::vector<CardConfig>& allCards, const std::map<std::string, int>& ownedCards);

private:
    QGridLayout* cardLayout;

    void setupUI();
    void updateCardDisplay(const std::vector<CardConfig>& cards, const std::map<std::string, int>& owned);
};

#endif // CARDDIALOG_HPP