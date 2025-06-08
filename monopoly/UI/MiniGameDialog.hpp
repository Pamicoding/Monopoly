#ifndef MINIGAMEDIALOG_HPP
#define MINIGAMEDIALOG_HPP

#include <QDialog>
#include <QPushButton>
#include <QStackedWidget>
#include <QString>

class MiniGameWidget; // 未來小遊戲介面會是這個

class MiniGameDialog : public QDialog {
    Q_OBJECT

public:
    explicit MiniGameDialog(QWidget* parent = nullptr);

private:
    QPushButton* game1Button;
    QPushButton* game2Button;
    QPushButton* game3Button;

    QStackedWidget* contentArea; // 放遊戲 widget 的地方

    void setupUI();
    void switchToGame(const QString& gameName);
};

#endif // MINIGAMEDIALOG_HPP