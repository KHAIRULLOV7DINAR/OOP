#include "../headers/ShipCollisionException.h"

ShipCollisionException::ShipCollisionException()
{
    message = "Ship collision";
}

const char* ShipCollisionException::what() const noexcept
{
    return message.c_str();
}