#include "../headers/OutOfBordersException.h"

OutOfBordersException::OutOfBordersException()
{
    message = "Given coordinates are out of borders";
}

const char* OutOfBordersException::what() const noexcept
{
    return message.c_str();
}