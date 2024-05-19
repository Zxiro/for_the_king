#ifndef ELEMENTNOTFOUNDEXCEPTION_H
#define ELEMENTNOTFOUNDEXCEPTION_H

#include <exception>

class ElementNotFoundException : public std::exception
{
public:
    const char* what()
    {
        return "Element not found in collection.";
    }
};

#endif