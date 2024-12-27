#ifndef SCANNER_BUILDER_H
#define SCANNER_BUILDER_H

#include "AbilityBuilder.h"


class ScannerBuilder: public AbilityBuilder
{
private:
public:
    ScannerBuilder();

    std::shared_ptr<Ability> BuildAbility(GameField& field, Coords coords, ShipManager& manager) override;

    Abilities GetName() override;

    ~ScannerBuilder() = default;
};


#endif