#ifndef OUT_OF_ABILITES_EXCEPTION_H
#define OUT_OF_ABILITIES_EXCEPTION_H

#include <exception>
#include <string>

class OutOfAbilitiesException : public std::exception
{
private:
	std::string message;

public:
	OutOfAbilitiesException();
    const char* what() const noexcept;
};

#endif