#pragma once
#include "Entity.h"

class Road : public Entity {
public:
    Road(const Position& pos) : Entity(pos, ".") {}

    bool isPassable() const override {
        return true;
    }
    bool canTeleport() const override {
        return true;
    }
};