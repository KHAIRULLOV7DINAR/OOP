#ifndef SHIP_SEGMENT_RANDOM_HIT_BUILDER_H
#define SHIP_SEGMENT_RANDOM_HIT_BUILDER_H

#include "AbilityBuilder.h"


class ShipSegmentRandomHitBuilder: public AbilityBuilder
{
private:
public:
    ShipSegmentRandomHitBuilder();

    std::shared_ptr<Ability> BuildAbility(GameField& field, Coords coords, ShipManager& manager) override;

    Abilities GetName() override;

    ~ShipSegmentRandomHitBuilder() = default;
};


#endif