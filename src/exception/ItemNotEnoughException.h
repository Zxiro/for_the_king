#ifndef ITEMNOTENOUGHEXCEPTION_H
#define ITEMNOTENOUGHEXCEPTION_H

#include <exception>

class ItemNotEnoughException : public std::exception
{
public:
    const char *what()
    {
        return "Item not enough.";
    }
};

#endif