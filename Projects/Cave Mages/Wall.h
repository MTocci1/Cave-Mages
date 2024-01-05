#pragma once
#include "Obstacle.h"

class Wall : public Obstacle
{
public:
	Wall();

	void virtual spawn(IntRect arena, Vector2f resolution, int tileSize);
};