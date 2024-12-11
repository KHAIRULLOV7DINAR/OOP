#include "../headers/AiPlayer.h"

AIPlayer::AIPlayer(ShipManager ship_manager, AbilityManager ability_manager, GameField& my_game_field): Player(ship_manager, ability_manager, my_game_field)
{
    width = this->GetGameField().GetWidth();
    height = this->GetGameField().GetWidth();
    for(int x_coord = 1; x_coord <= width; x_coord++)
    {
        for(int y_coord = 1; y_coord <= height; y_coord++)
        {
            non_attacked_cells.push_back(Coords{x_coord, y_coord});
            non_touched_cells.push_back(Coords{x_coord, y_coord});
        }
    }
}

void AIPlayer::AIAttack(GameField& enemy_game_field, ShipManager& enemy_ship_manager)
{
    std::mt19937 gen(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<> dis(0, non_attacked_cells.size() - 1);

    int random_cells_vec_index = dis(gen);
    Coords random_attack_coords = non_attacked_cells[random_cells_vec_index];
    non_attacked_cells.erase(non_attacked_cells.begin() + random_cells_vec_index);
    
    this->AttackEnemyField(random_attack_coords, enemy_game_field, enemy_ship_manager);
}

void AIPlayer::AIRandomPlaceShip()
{
    int int_orientation;
    ShipOrientation orientation;
    int amount_of_placed_ships = 0;

    while(amount_of_placed_ships != this->GetShipManager().GetAmountOfShips())
    {
        std::mt19937 gen(std::chrono::steady_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<> dis_c(0, non_touched_cells.size() - 1);
        std::uniform_int_distribution<> dis_o(0, 1);

        int random_cells_vec_index = dis_c(gen);
        switch(dis_o(gen))
        {
            case 0:
                orientation = ShipOrientation::Horizontal;
                break;
            case 1:
                orientation = ShipOrientation::Vertical;
                break;
        }
        Coords random_place_coords = non_attacked_cells[random_cells_vec_index];
        non_attacked_cells.erase(non_attacked_cells.begin() + random_cells_vec_index);

        try
        {
            this->PlaceShip(amount_of_placed_ships, random_place_coords, orientation);
            amount_of_placed_ships++;
        }
        catch(const std::exception& ex)
        {
            continue;
            // std::cout << ex.what() << std::endl;
        }
    }
}