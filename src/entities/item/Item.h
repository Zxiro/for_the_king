#ifndef ITEM_H
#define ITEM_H
#include "../Effect.h"

class Item: public Effect
{
public:
    virtual std::string getName() const
    {
        throw UnImplementException();
    }
};
#endif