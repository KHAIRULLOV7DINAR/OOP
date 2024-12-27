#include "../headers/Player.h"

Player::Player(ShipManager ship_manager, AbilityManager ability_manager, GameField& my_game_field):ship_manager(ship_manager), ability_manager(ability_manager), my_game_field(my_game_field){}


Player &Player::operator=(const Player &other)
{
    ship_manager = other.ship_manager;
    ability_manager = other.ability_manager;
    my_game_field = other.my_game_field;
}


bool Player::GetDDFlag()
{
    return DD_FLAG;
}

void Player::SetDDFlag(bool new_flag_value)
{
    DD_FLAG = new_flag_value;
}

void Player::AttackEnemyField(Coords given_coords, GameField& enemy_game_field, ShipManager& enemy_ship_manager)
{
    AttackResult ATTACK_FLAG = enemy_game_field.Attack(given_coords, this->GetDDFlag());

    switch(ATTACK_FLAG)
    {
    case AttackResult::DDAndDestroyed:
    {
        std::cout << "You got new ability!" << std::endl;
        this->SetDDFlag(false);
        this->AddAbility();
        enemy_ship_manager.NewDestroyedShip();
        break;
    }
    case AttackResult::DD:
    {
        this->SetDDFlag(false);
        break;
    }
    case AttackResult::Destroyed:
    {
        std::cout << "You got new ability!" << std::endl;
        this->AddAbility();
        enemy_ship_manager.NewDestroyedShip();
        break;
    }
    default:
        break;
    }
}


void Player::AddAbility()
{
    std::mt19937 genn(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<> diss(0, 2);
    int random_ability_number = diss(genn);

    switch(random_ability_number)
    {
    case 0:
    {
        ability_manager.PushAbility(std::make_shared<ShipSegmentRandomHitBuilder>());
        break;
    }
    case 1:
    {
        ability_manager.PushAbility(std::make_shared<ScannerBuilder>());
        break;
    }
    case 2:
    {
        ability_manager.PushAbility(std::make_shared<DoubleDamageBuilder>());
        break;
    }
    default:
        break;
    }
}

void Player::ExecuteAbility(Coords coords, GameField& enemy_game_field, ShipManager& enemy_ship_manager)
{
    bool EXECUTE_ABILITY_FLAG = ability_manager.ActivateAbility(enemy_game_field, coords, enemy_ship_manager);
    if(!EXECUTE_ABILITY_FLAG)
    {
        this->SetDDFlag(true);
    }
}

void Player::PrintMyBoard()
{
    my_game_field.Print();
}

void Player::PrintMyBoardHidden()
{
    my_game_field.PrintHidden();
}

void Player::PlaceShip(int index, Coords GivenCoords, ShipOrientation orientation)
{
    my_game_field.AddShip(ship_manager.GetShip(index), GivenCoords, orientation);
}

void Player::PrintMyShip(int index)
{
    ship_manager.GetShip(index).PrintShip();
}

int Player::GetAbilitySize()
{
    return ability_manager.GetAmountOfAbilities();
}

ShipManager& Player::GetShipManager()
{
    return ship_manager;
}


GameField& Player::GetGameField()
{
    return my_game_field;
}


void Player::SavePlayer(FileWrapper& file)
{
    file.write(ship_manager.GetAmountOfShips());
    file.write('\n');
    file.write(ship_manager.GetAmountOfIntactShips());
    file.write('\n');

    for (int i = 0; i < ship_manager.GetAmountOfShips(); i++)
    {
        file.write(static_cast<int>(ship_manager.GetShip(i).GetLength()));
        file.write(' ');
    }
    file.write('\n');
// 
    for (int i = 0; i < ship_manager.GetAmountOfShips(); i++)
    {
        file.write(static_cast<int>(ship_manager.GetShip(i).GetHeadCoords().x));
        file.write(' ');
        file.write(static_cast<int>(ship_manager.GetShip(i).GetHeadCoords().y));
        file.write(' ');
    }
    file.write('\n');
// 
    for (int i = 0; i < ship_manager.GetAmountOfShips(); i++)
    {
        file.write(static_cast<int>(ship_manager.GetShip(i).GetStatus()));
        file.write(' ');
    }
    file.write('\n');

    for (int i = 0; i < ship_manager.GetAmountOfShips(); i++)
    {
        file.write(static_cast<int>(const_cast<ShipManager&>(ship_manager).GetShip(i).GetOrientation()));
        file.write(' ');
        for (int j = 0; j < const_cast<ShipManager&>(ship_manager).GetShip(i).GetLength(); j++)
        {
            file.write(static_cast<int>(const_cast<ShipManager&>(ship_manager).GetShip(i).GetSegments()[j].status));
            file.write(' ');
        }
        file.write('\n');
    }
    my_game_field.SaveGameField(file);

    file.write(static_cast<int>(const_cast<AbilityManager&>(ability_manager).GetAmountOfAbilities()));
    file.write('\n');
    for (int i = 0; i < const_cast<AbilityManager&>(ability_manager).GetAmountOfAbilities(); i++)
    {
        file.write(static_cast<int>(const_cast<AbilityManager&>(ability_manager).GetAbilityNames()[i]));
        file.write(' ');
    }
    file.write('\n');
}


void Player::LoadPlayer(FileWrapper& file)
{
    std::vector<Lengths> length_of_ships;

    int amount_of_ships;
    int amount_of_intact_ships;

    file.read(amount_of_ships);
    file.read(amount_of_intact_ships);

    for (int i = 0; i < amount_of_ships; i++)
    {
        int n;
        file.read(n);
        length_of_ships.push_back(static_cast<Lengths>(n));
    }

    ship_manager.Rebuild(amount_of_ships, amount_of_intact_ships, length_of_ships);



 
    // for(int i = 0; i < ship_manager.GetShips().size(); i++)
    // {
    //     ship_manager.GetShip(i).PrintShip();
    // }
 


    
    for (int i = 0; i < amount_of_ships; i++)
    {
        int x, y;
        file.read(x);
        file.read(y);
        ship_manager.GetShip(i).SetHeadCoords(Coords{x, y});
    }

    for (int i = 0; i < amount_of_ships; i++)
    {
        int n;
        file.read(n);
        ship_manager.GetShip(i).SetStatus(static_cast<ShipStatus>(n));
    }

    for (int i = 0; i < amount_of_ships; i++)
    {
        int orientation;
        file.read(orientation);
        ship_manager.GetShip(i).SetOrientation(static_cast<ShipOrientation>(orientation));
        for (int j = 0; j < ship_manager.GetShip(i).GetLength(); j++)
        {
            int segment;
            file.read(segment);
            if (segment == 0)
            {
                ship_manager.GetShip(i).DamageShipSegment(j);
                ship_manager.GetShip(i).DamageShipSegment(j);
            }
            else if (segment == 1)
            {
                ship_manager.GetShip(i).DamageShipSegment(j);
            }
        }
    }
   my_game_field.LoadGameField(file);
   my_game_field.UpdatePointers(ship_manager);

    ability_manager.Clean();
    int count_abilities;
    file.read(count_abilities);
    for (int i = 0; i < count_abilities; i++)
    {
        int name;
        file.read(name);
        if(name == 0)
        {
            ability_manager.PushAbility(std::make_shared<DoubleDamageBuilder>());
        }
        else if(name == 1)
        {
            ability_manager.PushAbility(std::make_shared<ScannerBuilder>());
        }
        else if(name == 2)
        {
            ability_manager.PushAbility(std::make_shared<ShipSegmentRandomHitBuilder>());
        }
    }
}