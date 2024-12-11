#include "../headers/AbilityManager.h"


AbilityManager::AbilityManager()
{
    // abilities.push_back(std::make_shared<ShipSegmentRandomHitBuilder>());
    // abilities.push_back(std::make_shared<DoubleDamageBuilder>());
    // abilities.push_back(std::make_shared<ScannerBuilder>());

    std::vector<int> index_vec = {0, 1, 2};
    
    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(index_vec.begin(), index_vec.end(), g);

    for(int i = 0; i < 3; i++)
    {
        switch(index_vec[i])
        {
            case 0:
                abilities.push_back(std::make_shared<DoubleDamageBuilder>());
                break;
            case 1:
                abilities.push_back(std::make_shared<ShipSegmentRandomHitBuilder>());
                break;
            case 2:
                abilities.push_back(std::make_shared<DoubleDamageBuilder>());
                break;
            default:
                break;
        }
    }

}

AbilityManager::~AbilityManager()
{
    while (!abilities.empty())
    {
        abilities.erase(abilities.begin(), abilities.end());
    }
}


void AbilityManager::PushAbility(std::shared_ptr<AbilityBuilder> ability_builder)
{
    abilities.push_back(ability_builder);
}

void AbilityManager::CheckOutOfAbilities()
{
    if (abilities.empty())
    {
        throw OutOfAbilitiesException();
    }
}

std::shared_ptr<AbilityBuilder> AbilityManager::GetAbility()
{
    auto ability_builder = abilities[0];
    abilities.erase(abilities.begin());
    return ability_builder;
}

bool AbilityManager::ActivateAbility(GameField& field, Coords coords, ShipManager& manager)
{
    this->CheckOutOfAbilities();

    std::shared_ptr<AbilityBuilder> current_ability_builder = this->GetAbility();

    std::shared_ptr<Ability> current_ability = current_ability_builder->BuildAbility(field, coords, manager);
    bool result = current_ability->UseAbility();
    return result;
}

int AbilityManager::GetAmountOfAbilities()
{
    return abilities.size();
}

std::vector<Abilities> AbilityManager::GetAbilityNames()
{
    std::vector<Abilities> ability_names;
    for(int i = 0; i < this->GetAmountOfAbilities(); i++)
    {
        ability_names.push_back(abilities[i]->GetName());
    }
    return ability_names;
}

void AbilityManager::Clean()
{
    abilities.erase(abilities.begin(), abilities.end());
}