#ifndef ABILITY_H
#define ABILITY_H

#include "GameField.h"
#include <chrono>
#include <random>


class Ability
{
public:
    virtual int UseAbility() = 0;
    virtual ~Ability() = 0;
};

#endif 