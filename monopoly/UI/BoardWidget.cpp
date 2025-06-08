#include "BoardWidget.hpp"
#include <QPainter>
#include <QPaintEvent>
#include <QFont>
#include <QBrush>

BoardWidget::BoardWidget(QWidget* parent) : QWidget(parent) {}
BoardWidget::~BoardWidget() {}

QSize BoardWidget::sizeHint() const {
    return QSize(700, 500);  // 可以依據實際版面再調整
}

void BoardWidget::setStaticTileInfo(const std::vector<TileVisualInfo>& info) {
    tiles = info;
    update();
}

void BoardWidget::setOwnershipMap(const std::map<int, QColor>& ownership) {
    tileOwners = ownership;
    update();
}

void BoardWidget::setLevelMap(const std::map<int, int>& levels) {
    tileLevels = levels;
    update();
}

void BoardWidget::setPlayerMap(const std::map<int, std::vector<QColor>>& players) {
    tilePlayers = players;
    update();
}

void BoardWidget::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    for (size_t i = 0; i < tiles.size(); ++i) {
        auto [row, col] = getGridPosition(static_cast<int>(i));
        drawTile(painter, static_cast<int>(i), row, col);
    }
}

void BoardWidget::drawTile(QPainter& painter, int index, int row, int col) {
    int x = col * (TILE_WIDTH + TILE_SPACING);
    int y = row * (TILE_HEIGHT + TILE_SPACING);
    QRect rect(x, y, TILE_WIDTH, TILE_HEIGHT);

    // 背景顏色：地主顏色 or default
    if (tileOwners.count(index)) {
        painter.setBrush(tileOwners.at(index));
    } else {
        painter.setBrush(QColor(220, 220, 220));  // 淺灰
    }
    painter.setPen(Qt::black);
    painter.drawRect(rect);

    // 地塊名稱
    if (index < static_cast<int>(tiles.size())) {
        const auto& info = tiles[index];
        painter.setFont(QFont("Arial", 8));
        painter.drawText(rect.adjusted(2, 2, -2, -TILE_HEIGHT / 2), Qt::AlignTop | Qt::AlignHCenter, QString::fromStdString(info.name));
    }

    // 地塊等級（畫小房子）
    if (tileLevels.count(index)) {
        int level = tileLevels.at(index);
        for (int i = 0; i < level && i < 3; ++i) {
            QRect house(x + 5 + i * 15, y + TILE_HEIGHT - 15, 10, 10);
            painter.setBrush(Qt::black);
            painter.drawRect(house);
        }
    }

    // 玩家圖示（最多畫 3 個小圓）
    if (tilePlayers.count(index)) {
        const auto& colors = tilePlayers.at(index);
        int cx = x + 8;
        int cy = y + 20;
        for (size_t i = 0; i < colors.size() && i < 3; ++i) {
            painter.setBrush(colors[i]);
            painter.drawEllipse(QRect(cx, cy + static_cast<int>(i) * 15, 12, 12));
        }
    }
}

std::pair<int, int> BoardWidget::getGridPosition(int index) const {
    if (index >= 0 && index < 8) {
        return {0, index};                // 上排
    } else if (index >= 8 && index < 14) {
        return {index - 7, 7};            // 右側
    } else if (index >= 14 && index < 22) {
        return {6, 21 - index};           // 下排（反向）
    } else {
        return {28 - index, 0};           // 左側（反向）
    }
}