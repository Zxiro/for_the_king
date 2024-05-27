#ifndef ITEM_H
#define ITEM_H
#include <string>

#include "../Effect.h"

class Item: public Effect
{
public:
    virtual std::string getName() const = 0;
};
#endif