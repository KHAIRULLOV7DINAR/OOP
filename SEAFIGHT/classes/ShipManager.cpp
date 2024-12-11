#include "../headers/ShipManager.h"

ShipManager::ShipManager(int amount_of_ships, std::vector<Lengths> lengths):amount_of_ships(amount_of_ships), amount_of_intact_ships(amount_of_ships)
{
    for (int i = 0; i < amount_of_ships; i++)
    {
        this->CreateShip(lengths[i], ShipOrientation::Horizontal);
        // std::cout << ships.size() << std::endl;
    }
}

int ShipManager::GetAmountOfShips() const
{
    return amount_of_ships;
}


int ShipManager::GetAmountOfIntactShips() const
{
    return amount_of_intact_ships;
}


void ShipManager::NewDestroyedShip()
{
    amount_of_intact_ships--;
}


std::vector<Ship> ShipManager::GetShips() const
{
    return ships;
}

void ShipManager::CreateShip(Lengths length, ShipOrientation orientation)
{
    ships.push_back(Ship(length, orientation));
}

Ship& ShipManager::GetShip(int index)
{
    Ship& s_ship = ships[index];
    return ships[index];
}


const Ship& ShipManager::GetShip(int index) const
{
    return ships[index];
}


void ShipManager::Clean()
{
    ships.erase(ships.begin(), ships.end());
    amount_of_ships = 0;
    amount_of_intact_ships = 0;
}

void ShipManager::Rebuild(int amount_of_ships, int amount_of_intact_ships, std::vector<Lengths> lengths)
{
    this->Clean();
    this->amount_of_ships = amount_of_ships;
    this->amount_of_intact_ships = amount_of_intact_ships;

    std::cout << "AOS " << this->amount_of_ships << std::endl;

    for (int i = 0; i < amount_of_ships; i++)
    {
        this->CreateShip(lengths[i], ShipOrientation::Horizontal);
    }
}


void ShipManager::PrintDebug()
{
    std::cout << ships.size() << std::endl;
    std::cout << amount_of_ships << std::endl;
}

