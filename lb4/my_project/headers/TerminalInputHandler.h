#ifndef TREMINAL_INPUT_HANDLER_H
#define TREMINAL_INPUT_HANDLER_H

#include <iostream>
#include <map>
#include <limits>
#include <set>
#include "FileWrapper.h"
#include "GameField.h"
#include "InputException.h"
#include <sstream>

class TerminalInputHandler
{
private:
    std::map<char, Command> commands_map;
    std::map<std::string, Command> string_commands;

public:
    TerminalInputHandler();

    void LoadCommands(const std::string& filename);
    void DefaultArguments();
    Command CommandInput();
    std::map<char, Command> GetMapOfCommands() const;
    Coords CoordsInput(int width, int height);
    ShipOrientation OrientationInput();
};

#endif