#ifndef MONEYNOTENOUGHEXCEPTION_H
#define MONEYNOTENOUGHEXCEPTION_H

#include <exception>

class MoneyNotEnoughException : public std::exception
{
public:
    const char *what()
    {
        return "Money not enough.";
    }
};

#endif