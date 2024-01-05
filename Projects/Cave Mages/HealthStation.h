#pragma once
#include "Obstacle.h"

class HealthStation : public Obstacle
{
public:
	HealthStation();

	void virtual spawn(IntRect arena, Vector2f resolution, int tileSize);
};