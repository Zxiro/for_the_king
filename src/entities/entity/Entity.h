#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include "../../structs/Position.h"

class Entity
{
public:
    Entity(const Position& _position, const std::string& _display)
        : position(_position), display(_display) {}

    Position getPosition() const {
        return position;
    }

    void setPosition(const Position& pos)
    {
        this->position = pos;
    }

    std::string getDisplay() const {
        return display;
    }

    virtual bool isPassable() const = 0;

protected:
    Position position;
    std::string display;
};

#endif // ENTITY_H
