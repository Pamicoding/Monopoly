#ifndef SUDODIALOG_HPP
#define SUDODIALOG_HPP

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <functional>
#include "SudoCommand.hpp"
#include "SudoCommandParser.hpp"

class SudoDialog : public QDialog {
    Q_OBJECT

public:
    explicit SudoDialog(QWidget* parent = nullptr);

    // 綁定實際執行 callback（可由 MainWindow 傳入 Game 執行）
    void setExecutor(std::function<void(const ParsedCommand&)> func);

private:
    QLineEdit* inputField;
    QPushButton* execButton;
    QLabel* resultLabel;

    SudoCommandParser parser;
    std::function<void(const ParsedCommand&)> executor;

    void setupUI();
    void onCommandEntered();
};

#endif // SUDODIALOG_HPP