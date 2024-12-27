#include "../headers/TerminalOutputHandler.h"


TerminalOutputHandler::TerminalOutputHandler()
{
}


void TerminalOutputHandler::PrintString(std::string message)
{
    std::cout << message << std::endl;
}


void TerminalOutputHandler::PrintRound(int number)
{
    std::cout << "ROUND NUMBER " << number <<std::endl;
}

