#pragma once
#include <string>

#include "../../structs/Position.h"

class Entity {
public:
    Entity(Position pos, std::string display)
    {
        this->position = pos;
        this->display = display;
    }

    Position getPosition() const
    {
        return this->position;
    }
private:
    Position position;
    // The string displayed on the map
    std::string display;
};
