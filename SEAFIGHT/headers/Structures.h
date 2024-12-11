#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <memory>
#include "OutOfBordersException.h"
#include "ShipCollisionException.h"
#include "AttackException.h"

enum Lengths
{
  One = 1,
  Two = 2,
  Three = 3,
  Four = 4
};

enum  ShipOrientation
{
Vertical = 0,
Horizontal = 1
};

enum class ShipSegmentStatus
{
Intact = 2,
Damaged = 1,
Destroyed = 0
};

enum class ShipStatus
{
Intact = 2,
Damaged = 1,
Destroyed = 0
};

enum class CellStatus
{
  Empty = 0,
  Ship = 1,
  DamagedShip = 2,
  DestroyedShip = 3,
  Unknown = 4,
  SecretlyDamamged = 5,
  SecretlyDestroyed = 6
};

enum class Abilities
{
  DoubleDamage = 0,
  Scanner = 1,
  ShipSegmentRandomHit = 2
};

enum class AttackResult
{
  DDAndDestroyed,
  DD,
  Destroyed,
  Nothing,
};

struct Coords
{
  int x;
  int y;

  bool operator==(const Coords &other) const{
    return x == other.x && y == other.y;
  }

};

struct ShipSegment
{
  ShipSegmentStatus status;
};



#endif