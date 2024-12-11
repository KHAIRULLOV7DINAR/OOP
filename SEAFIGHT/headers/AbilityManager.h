#ifndef ABILITY_MANAGER_H
#define ABILITY_MANAGER_H

#include "Ability.h"
#include "AbilityBuilder.h"
#include "ScannerBuilder.h"
#include "DoubleDamageBuilder.h"
#include "ShipSegmentRandomHitBuilder.h"
#include "OutOfAbilitiesException.h"

#include <queue>

class AbilityManager
{
private:
    std::vector <std::shared_ptr<AbilityBuilder>> abilities;

public:
    AbilityManager();
    ~AbilityManager();

   void PushAbility(std::shared_ptr<AbilityBuilder> ability_builder);
   void CheckOutOfAbilities();
   std::shared_ptr<AbilityBuilder> GetAbility();
   bool ActivateAbility(GameField& field, Coords coords, ShipManager& manager);
   int GetAmountOfAbilities();
   std::vector<Abilities> GetAbilityNames();
   void Clean();
};

#endif