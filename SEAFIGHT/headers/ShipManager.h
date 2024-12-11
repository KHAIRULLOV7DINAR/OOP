#ifndef SHIP_MANAGER_H
#define SHIP_MANAGER_H

#include <vector>
#include <iostream>
#include "Ship.h"

class ShipManager
{
private:

    std::vector<Ship> ships;
    int amount_of_ships;
    int amount_of_intact_ships;

public:
    ShipManager(int amount_of_ships, std::vector<Lengths> sizes);
    ~ShipManager() {};

    int GetAmountOfShips() const;
    int GetAmountOfIntactShips() const;
    void NewDestroyedShip();
    std::vector<Ship> GetShips() const;
    Ship& GetShip(int index);
    const Ship& GetShip(int index) const;

    void CreateShip(Lengths length, ShipOrientation orientation = ShipOrientation::Horizontal);
    void Clean();
    void Rebuild(int amound_of_ships, int amount_of_intact_ships, std::vector<Lengths> lengths);
    void PrintDebug();

};

#endif