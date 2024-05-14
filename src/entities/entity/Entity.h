#ifndef ENTITY_H
#define ENTITY_H

#include <string>

#include "../../structs/Position.h"

class Entity
{
public:
    Entity(const Position &_position, const std::string &_display)
    {
        position = _position;
        display = _display;
    }

    Position getPosition() const
    {
        return position;
    }

    std::string getDisplay()
    {
        return display;
    }

protected:
    Position position;
    // The string displayed on the map
    std::string display;
};

#endif