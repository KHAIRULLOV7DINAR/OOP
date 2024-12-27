#include "../headers/AttackException.h"

AttackException::AttackException()
{
    message = "You can't attack this cell!";
}

const char* AttackException::what() const noexcept
{
    return message.c_str();
}