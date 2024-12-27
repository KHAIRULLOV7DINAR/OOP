#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <stdlib.h>

#include "AIPlayer.h"
#include "GameState.h"
#include "SavingsHandler.h"

class Game
{
private:
    bool game_flag = true;

    GameState* game_state;
    SavingsHandler* savings_handler;
    GameField& player_game_field;
    GameField& ai_player_game_field;
    Player* human_player;
    AIPlayer* ai_player;
public:
    Game(GameField& player_game_field, GameField& ai_player_game_field);
    ~Game();
    void Reset();
    void PlacingShips(int amount_of_placed_ships, Coords coords, ShipOrientation orientation);
    void AIPlacingShips();
    void Save();
    void Load();
    void PlayerAttack(Coords coords);
    void AIPlayerAttack();
    void PlayerUseAbility(Coords coords);
    Player* GetPlayer();
    GameState& GetGameState();
    AIPlayer* GetAIPlayer();
};

#endif 
