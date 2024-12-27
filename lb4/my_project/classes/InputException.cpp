#include "../headers/InputException.h"

InputException::InputException()
{
    message = "Invalid input data!";
}

const char* InputException::what() const noexcept
{
    return message.c_str();
}