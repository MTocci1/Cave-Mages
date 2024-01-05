#pragma once
#include "Obstacle.h"

class Water : public Obstacle
{
public:
	Water();

	void virtual spawn(IntRect arena, Vector2f resolution, int tileSize);
};