#ifndef AI_PLAYER_H
#define AI_PLAYER_H

#include "ShipManager.h"
#include "GameField.h"
#include "AbilityManager.h"
#include "Player.h"

class AIPlayer: public Player
{
private:
    std::vector<Coords> non_attacked_cells;
    std::vector<Coords> non_touched_cells;
    int width;
    int height;
public:

    AIPlayer(ShipManager ship_manager, AbilityManager ability_manager, GameField& my_game_field);
    ~AIPlayer() = default;

    void AIAttack(GameField& enemy_game_field, ShipManager& enemy_ship_manager);
    void AIRandomPlaceShip();
};


#endif