#ifndef PROPERTY_TILE_HPP
#define PROPERTY_TILE_HPP

#include "Tile.hpp"
#include <memory>

class PropertyTile : public Tile {
private:
    int level;
    std::shared_ptr<Player> owner;

public:
    PropertyTile(std::size_t id, const std::string& name);

    void upgrade(); // 將等級升級（最多 3 級）
    void setOwner(std::shared_ptr<Player> p);
    std::shared_ptr<Player> getOwner() const;
    int getLevel() const;

    TileAction landOn(std::shared_ptr<Player> player) override;
};

#endif // PROPERTY_TILE_HPP
