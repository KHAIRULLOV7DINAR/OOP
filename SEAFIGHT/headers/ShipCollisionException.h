#ifndef SHIP_COLLISION_EXCEPTION_H
#define SHIP_COLLISION_EXCEPTION_H

#include <exception>
#include <string>

class ShipCollisionException : public std::exception
{
private:
	std::string message;

public:
	ShipCollisionException();
    const char* what() const noexcept;
};

#endif