#include "../headers/ShipSegmentRandomHitBuilder.h"

ShipSegmentRandomHitBuilder::ShipSegmentRandomHitBuilder(){}

std::shared_ptr<Ability> ShipSegmentRandomHitBuilder::BuildAbility(GameField& field, Coords coords, ShipManager& manager)
{
    return std::make_shared<ShipSegmentRandomHit>(field, manager);
}

Abilities ShipSegmentRandomHitBuilder::GetName()
{
    return Abilities::ShipSegmentRandomHit;
}