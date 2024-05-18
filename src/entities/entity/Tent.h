#ifndef TENT_H
#define TENT_H

#include "Entity.h"

class Tent : public Entity
{
public:
    Tent() : Entity(Position{ 0, 0 }, "Tent") {}
    Tent(const Position& pos)
        : Entity(pos, "Tent") {}

    bool isPassable() const override {
        return true;
    }
};

#endif