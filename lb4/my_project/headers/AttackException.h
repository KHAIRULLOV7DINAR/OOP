#ifndef ATTACK_EXCEPTION_H
#define ATTACK_EXCEPTION_H

#include <exception>
#include <string>

class AttackException : public std::exception
{
private:
	std::string message;

public:
	AttackException();
    const char* what() const noexcept;
};

#endif