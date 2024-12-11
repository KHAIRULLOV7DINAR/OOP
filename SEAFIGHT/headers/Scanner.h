#ifndef SCANNER_H
#define SCANNER_H

#include "Ability.h"

class Scanner : public Ability
{
private:
	GameField& field;
	Coords coords;
public:
	Scanner(GameField& field, Coords coords);
	int UseAbility() override;

	~Scanner() = default;
};

#endif