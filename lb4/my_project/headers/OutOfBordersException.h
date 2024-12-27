#ifndef OUT_OF_BORDERS_EXCEPTION_H
#define OUT_OF_BORDERS_EXCEPTION_H

#include <exception>
#include <string>

class OutOfBordersException : public std::exception
{
private:
	std::string message;

public:
	OutOfBordersException();
    const char* what() const noexcept;
};

#endif