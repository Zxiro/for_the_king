#include <vector>
#include <memory>
#include "../entities/entity/Store.h"

class Board {
public:
    Board(int width, int height) : width(width), height(height) {
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
