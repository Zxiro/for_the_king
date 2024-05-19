#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <vector>
#include <memory>
#include "../entities/entity/Entity.h"
#include "../entities/entity/Wall.h"
#include "../entities/entity/Store.h"
#include "../entities/entity/creature/Player.h"
#include "../entities/entity/Tent.h"
#include "../entities/entity/RandomEvent.h"

class GameMap {
public:
    GameMap(int width, int height) : width(width), height(height) {
        map.resize(height, std::vector<std::shared_ptr<Entity>>(width, nullptr));
    }

    void addEntity(std::shared_ptr<Entity> entity, int x, int y) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            map[y][x] = entity;
        }
    }

    bool isPassable(int x, int y) const {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            if (map[y][x]) {
                return map[y][x]->isPassable();
            }
            return true; // if no entity, it's passable
        }
        return false; // out of bounds
    }

    std::shared_ptr<Entity> getEntity(int x, int y) const {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            return map[y][x];
        }
        return nullptr;
    }

private:
    int width;
    int height;
    std::vector<std::vector<std::shared_ptr<Entity>>> map;
};

#endif // GAMEMAP_H
