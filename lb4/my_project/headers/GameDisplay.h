#ifndef GAME_DISPLAY_H
#define GAME_DISPLAY_H

#include <iostream>
#include "TerminalInputHandler.h"
#include "TerminalOutputHandler.h"
#include "Game.h"

template <typename RenderType, typename OutputType>
class GameDisplay
{
private:
    OutputType* output;
    RenderType renderer;

public:
    GameDisplay();
    void PrintPlayerField(GameField& game_field);
    void PrintEnemyField(GameField& game_field);
    void PrintRound(int amount_of_rounds);
    void Print(std::string message);
};

#endif