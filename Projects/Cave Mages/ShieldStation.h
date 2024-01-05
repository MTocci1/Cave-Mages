#pragma once
#include "Obstacle.h"

class ShieldStation : public Obstacle
{
public:
	ShieldStation();

	void virtual spawn(IntRect arena, Vector2f resolution, int tileSize);
};