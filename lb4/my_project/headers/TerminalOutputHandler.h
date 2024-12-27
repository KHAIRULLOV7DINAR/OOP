#ifndef TERMINAL_OUTPUT_HANDLER_H
#define TERMINAL_OUTPUT_HANDLER_H

#include <iostream>
#include <map>
#include "FieldRenderer.h"
#include "GameField.h"
#include "FileWrapper.h"

class TerminalOutputHandler
{
private:
public:
    TerminalOutputHandler();

    void PrintRound(int number);
    void PrintString(std::string message);
};

#endif