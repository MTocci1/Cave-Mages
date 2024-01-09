#pragma once
#include "Enemy.h"

class Ghost : public Enemy
{
public:
	Ghost();

	void hitPlayer(int& enemiesLeft);

	// The overriden input handler for Ghost
	void virtual update(float elapsedTime, bool playerFacingDirection, Vector2f playerPosition);

	// Check if the player is in enemy range
	void virtual isPlayerInRange(Vector2f playerPosition);

	void setFacingDirection(bool isAimingRight);
};