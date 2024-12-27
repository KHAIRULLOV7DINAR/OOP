#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <iostream>
#include "TerminalInputHandler.h"
#include "Game.h"
#include "FieldRenderer.h"
#include "TerminalInputHandler.h"
#include "TerminalOutputHandler.h"
#include "GameDisplay.h"

template <typename InputType, typename OutputType, typename RendererType>
class GameController
{
private:
    Game& game;

    InputType* input_handler;
    GameDisplay<RendererType, OutputType>* game_display;

    bool game_flag = true;
    bool load_flag = false;

public:
    GameController(Game& game);
    ~GameController();
    void StartGame();
    bool GameMenu();
    void PlayerTurn();
    void AIPlayerTurn();
};

#endif