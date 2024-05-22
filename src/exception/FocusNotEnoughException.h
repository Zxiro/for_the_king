#ifndef FOCUSNOTENOUGHEXCEPTION_H
#define FOCUSNOTENOUGHEXCEPTION_H

#include <exception>

class FocusNotEnoughException : public std::exception
{
public:
    const char* what()
    {
        return "Focus not enough.";
    }
};

#endif