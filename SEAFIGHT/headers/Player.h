#ifndef PLAYER_H
#define PLAYER_H

#include "ShipManager.h"
#include "GameField.h"
#include "AbilityManager.h"
#include "FileWrapper.h"

class Player
{
protected:
    bool DD_FLAG = 0;
    ShipManager ship_manager;
    AbilityManager ability_manager;
    GameField& my_game_field;

public:
    Player(ShipManager ship_manager, AbilityManager ability_manager, GameField& my_game_field);
    Player& operator=(const Player &other);
    ~Player() = default;
    bool GetDDFlag();
    void SetDDFlag(bool new_flag_value);
    void AttackEnemyField(Coords given_coords, GameField& enemy_game_field, ShipManager& enemy_ship_manager);
    void AddAbility();
    void ExecuteAbility(Coords coords, GameField& enemy_game_field, ShipManager& enemy_ship_manager);
    void PrintMyBoard();
    void PrintMyBoardHidden();
    void PlaceShip(int index, Coords GivenCoords, ShipOrientation orientation);
    void PrintMyShip(int index);
    int GetAbilitySize();
    ShipManager& GetShipManager();
    GameField& GetGameField();
    void SavePlayer(FileWrapper& file);
    void LoadPlayer(FileWrapper& file);
};


#endif