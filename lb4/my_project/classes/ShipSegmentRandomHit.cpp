#include "../headers/ShipSegmentRandomHit.h"

ShipSegmentRandomHit::ShipSegmentRandomHit(GameField& field, ShipManager& manager):field(field), manager(manager){}

int ShipSegmentRandomHit::UseAbility()
{
    std::vector<int> intact_ships_indexes;
    std::vector<int> intact_ships_segment_indexes;

    for(int index = 0; index < manager.GetAmountOfShips(); index++)
    {
        if(manager.GetShip(index).GetStatus() == ShipStatus::Damaged || manager.GetShip(index).GetStatus() == ShipStatus::Intact)
        {
            intact_ships_indexes.push_back(index);
        }
    }

	if (!intact_ships_indexes.empty())
    {

		std::mt19937 gen(std::chrono::steady_clock::now().time_since_epoch().count());
		std::uniform_int_distribution<> dis(0, intact_ships_indexes.size() - 1);

		int random_ship_index = intact_ships_indexes[dis(gen)];

        const std::vector<ShipSegment> ships_segments = manager.GetShip(random_ship_index).GetSegments();
        for(int index = 0; index < ships_segments.size(); index++)
        {
            if(ships_segments[index].status == ShipSegmentStatus::Intact || ships_segments[index].status == ShipSegmentStatus::Damaged)
            {
                intact_ships_segment_indexes.push_back(index);
            }
        }

		std::mt19937 genn(std::chrono::steady_clock::now().time_since_epoch().count());
		std::uniform_int_distribution<> diss(0, intact_ships_segment_indexes.size() - 1);
        int random_ship_segment_index = intact_ships_segment_indexes[diss(genn)];

        Coords attack_coords = manager.GetShip(random_ship_index).GetHeadCoords();
        if(manager.GetShip(random_ship_index).GetOrientation() == ShipOrientation::Horizontal)
        {
            attack_coords.x = attack_coords.x + random_ship_segment_index;
        }
        else
        {
            attack_coords.y = attack_coords.y + random_ship_segment_index;
        }

        field.ShipSegmentRandomHitAttack(attack_coords);

        // manager.GetShip(random_ship_index).PrintShip();
	}
    std::cout << "Ship segment random hit was used!" << std::endl;
    return 2;
}