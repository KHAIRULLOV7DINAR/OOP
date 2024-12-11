#ifndef DOUBLE_DAMAGE_H
#define DOUBLE_DAMAGE_H

#include "Ability.h"

class DoubleDamage : public Ability
{
private:
public:
	DoubleDamage();
	int UseAbility() override;

	~DoubleDamage() = default;
};

#endif