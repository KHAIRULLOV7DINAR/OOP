#include "../headers/ScannerBuilder.h"

ScannerBuilder::ScannerBuilder(){}

std::shared_ptr<Ability> ScannerBuilder::BuildAbility(GameField& field, Coords coords, ShipManager& manager)
{
    return std::make_shared<Scanner>(field, coords);
}

Abilities ScannerBuilder::GetName()
{
    return Abilities::Scanner;
}

