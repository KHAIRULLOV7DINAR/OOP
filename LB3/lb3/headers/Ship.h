#ifndef SHIP_H
#define SHIP_H

#include "Structures.h"

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>

class Ship
{
private:
  ShipStatus status;
  Lengths length;
  ShipOrientation orientation;
  std::vector<ShipSegment> segments;
  Coords head_coords;

public:
    Ship(Lengths length);
    Ship(Lengths length, ShipOrientation orientation);
    ~Ship() {};


    Lengths GetLength() const;
    const ShipOrientation GetOrientation() const;
    const std::vector<ShipSegment> GetSegments() const;
    ShipStatus GetStatus();

    void SetOrientation(ShipOrientation orientation);
    bool IsDestroyed() const;
    void ShipStatusUpdate();
    void DamageShipSegment(int segIndex);
    void PrintShip() const;
    void SetStatus(ShipStatus status);
    void SetHeadCoords(Coords coords);
    Coords GetHeadCoords();

};

#endif