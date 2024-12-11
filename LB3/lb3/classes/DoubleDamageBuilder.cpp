#include "../headers/DoubleDamageBuilder.h"

DoubleDamageBuilder::DoubleDamageBuilder(){}

std::shared_ptr<Ability> DoubleDamageBuilder::BuildAbility(GameField& field, Coords coords, ShipManager& manager)
{
    return std::make_shared<DoubleDamage>();
}

Abilities DoubleDamageBuilder::GetName()
{
    return Abilities::DoubleDamage;
}