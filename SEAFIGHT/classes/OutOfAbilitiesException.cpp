#include "../headers/OutOfAbilitiesException.h"

OutOfAbilitiesException::OutOfAbilitiesException()
{
    message = "You are out of abilities to use";
}

const char* OutOfAbilitiesException::what() const noexcept
{
    return message.c_str();
}