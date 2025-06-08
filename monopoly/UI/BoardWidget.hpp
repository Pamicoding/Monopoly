#ifndef BOARDWIDGET_HPP
#define BOARDWIDGET_HPP

#include <QWidget>
#include <QColor>
#include <vector>
#include <map>
#include <string>

struct TileVisualInfo {
    int id;
    std::string name;
    std::string type;
};

class BoardWidget : public QWidget {
    Q_OBJECT

public:
    explicit BoardWidget(QWidget* parent = nullptr);
    ~BoardWidget();

    QSize sizeHint() const override;
    void setStaticTileInfo(const std::vector<TileVisualInfo>& info);
    void setOwnershipMap(const std::map<int, QColor>& ownership);
    void setLevelMap(const std::map<int, int>& levels);
    void setPlayerMap(const std::map<int, std::vector<QColor>>& players);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    // Tile 資訊
    std::vector<TileVisualInfo> tiles;

    // tileId → 擁有者顏色 / 等級 / 玩家 icon 顏色
    std::map<int, QColor> tileOwners;
    std::map<int, int> tileLevels;
    std::map<int, std::vector<QColor>> tilePlayers;

    static constexpr int TILE_WIDTH = 60;
    static constexpr int TILE_HEIGHT = 60;
    static constexpr int TILE_SPACING = 5;

    std::pair<int, int> getGridPosition(int index) const;
    void drawTile(QPainter& painter, int index, int row, int col);
};

#endif // BOARDWIDGET_HPP