#ifndef ABILITY_BUILDER_H
#define ABILITY_BUILDER_H

#include <iostream>
#include <memory>
#include "GameField.h"
#include "Ability.h"
#include "ShipManager.h"
#include "DoubleDamage.h"
#include "Scanner.h"
#include "ShipSegmentRandomHit.h"

class AbilityBuilder
{
public:
    virtual std::shared_ptr<Ability> BuildAbility(GameField& field, Coords coords, ShipManager& manager) = 0;
    virtual Abilities GetName() = 0;
    virtual ~AbilityBuilder() = 0;
};

#endif