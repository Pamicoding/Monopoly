#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include "BoardWidget.hpp"
#include "PlayerPanel.hpp"
#include "SudoCommand.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

    // 若未來有設計：重新刷新 UI 顯示（ex. sudo 調整後更新畫面）
    void refresh();

private:
    BoardWidget* boardWidget;
    PlayerPanel* playerPanel;

    void setupUI();
};

#endif // MAINWINDOW_HPP