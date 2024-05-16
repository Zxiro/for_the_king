#ifndef UN_IMPLEMENT_EXCEPTION_H
#define UN_IMPLEMENT_EXCEPTION_H

#include <exception>

class UnImplementException : public std::exception
{
public:
    const char *what()
    {
        return "Method UnImplement";
    }
};

#endif