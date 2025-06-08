#ifndef PLAYERPANEL_HPP
#define PLAYERPANEL_HPP

#include <QWidget>
#include <vector>
#include <QString>
#include <QColor>

struct PlayerDisplayInfo {
    int rank;
    QString name;
    QPixmap icon;
    QColor color;
    long long money;
    QString status;
    bool isCurrentTurn;
};

class PlayerPanel : public QWidget {
    Q_OBJECT

public:
    explicit PlayerPanel(QWidget* parent = nullptr);
    void setPlayerList(const std::vector<PlayerDisplayInfo>& players);

private:
    void refreshLayout();
    std::vector<PlayerDisplayInfo> currentPlayers;
};

#endif // PLAYERPANEL_HPP