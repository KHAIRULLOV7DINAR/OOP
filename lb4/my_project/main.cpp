#include <iostream>
#include <vector>


#include "headers/ShipManager.h"
#include "headers/GameField.h"
#include "headers/AbilityManager.h"
#include "headers/Player.h"
#include "headers/AIPlayer.h"
#include "headers/InputHandler.h"
#include "headers/GameDisplay.h"
#include "headers/GameController.h"


int main()
{
    GameField player_game_field(10, 10);
    GameField ai_player_game_field(10, 10);

    Game game(player_game_field, ai_player_game_field);
    auto game_controller = GameController<TerminalInputHandler, TerminalOutputHandler, FieldRenderer>(game);
    game_controller.StartGame();
}