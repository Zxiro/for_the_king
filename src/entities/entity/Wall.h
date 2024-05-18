#ifndef WALL_H
#define WALL_H

#include "Entity.h"

class Wall : public Entity {
public:
    Wall() : Entity(Position{ 0, 0 }, "Wall") {}
    Wall(const Position& pos) : Entity(pos, "Wall") {}

    bool isPassable() const override {
        return false;
    }
};

#endif // WALL_H