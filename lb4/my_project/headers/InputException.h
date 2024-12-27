#ifndef INPUT_EXCEPTION_H
#define INPUT_EXCEPTION_H

#include <exception>
#include <string>

class InputException : public std::exception
{
private:
	std::string message;

public:
	InputException();
    const char* what() const noexcept;
};

#endif