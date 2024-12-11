#ifndef DOUBLE_DAMAGE_BUILDER_H
#define DOUBLE_DAMAGE_BUILDER_H

#include "AbilityBuilder.h"


class DoubleDamageBuilder: public AbilityBuilder
{
private:
public:
    DoubleDamageBuilder();

    std::shared_ptr<Ability> BuildAbility(GameField& field, Coords coords, ShipManager& manager) override;

    Abilities GetName() override;

    ~DoubleDamageBuilder() = default;
};


#endif