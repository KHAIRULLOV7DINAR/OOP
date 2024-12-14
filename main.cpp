#include <iostream>
#include <vector>


#include "headers/ShipManager.h"
#include "headers/GameField.h"
#include "headers/AbilityManager.h"
#include "headers/Player.h"
#include "headers/AIPlayer.h"
#include "headers/Game.h"


int main()
{
    GameField player_game_field(10, 10);
    GameField ai_player_game_field(10, 10);

    Game game(player_game_field, ai_player_game_field);
    game.StartGame();
}