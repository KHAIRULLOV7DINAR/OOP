#ifndef SHIP_SEGMENT_RANDOM_HIT_H
#define SHIP_SEGMENT_RANDOM_HIT_H

#include "Ability.h"
#include "ShipManager.h"

class ShipSegmentRandomHit :public Ability
{
private:
	GameField& field;
	ShipManager& manager;
public:
	ShipSegmentRandomHit(GameField& field, ShipManager& manager);
	int UseAbility()  override;

	~ShipSegmentRandomHit() = default;
};

#endif