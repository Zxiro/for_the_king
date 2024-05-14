#ifndef EXCEPTION_H
#define EXCEPTION_H

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