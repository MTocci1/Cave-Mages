#pragma once
#include "XP.h"

class Silver : public XP
{
private:

public:
	Silver(float positionX, float positionY, IntRect arena, Vector2f resolution, int tileSize);

	// The overriden input handler for XP
	void virtual update(float elapsedTime, Vector2f playerPosition);

	// Check if the player is in enemy range
	void virtual isPlayerInRange(Vector2f playerPosition);
};