#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <stdlib.h>

#include "AIPlayer.h"
#include "GameState.h"
#include "InputHandler.h"
#include "SavingsHandler.h"

class Game
{
private:
    bool game_flag = true;

    GameState* game_state;
    InputHandler* input_handler;
    SavingsHandler* savings_handler;
    GameField& player_game_field;
    GameField& ai_player_game_field;
    Player* human_player;
    AIPlayer* ai_player;
public:
    Game(GameField& player_game_field, GameField& ai_player_game_field);
    ~Game();
    void Menu();
    void StartGame();
    void Reset();
    void PlacingShips();
    void AIPlacingShips();
    void PlayerTurn();
    void AIPlayerTurn();
};

#endif 
