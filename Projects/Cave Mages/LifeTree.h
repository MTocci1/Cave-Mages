#pragma once
#include "Deployable.h"

class LifeTree : public Deployable
{
private:
	int m_HealAmount;

	bool m_isPlayerInRange;

	int m_FireRate;
	Time LastShot;
	

public:
	LifeTree(Vector2f position);

	// The overriden input handler for tree
	void virtual update(float elapsedTime, Vector2f targetPosition);

	// Check if the player is in tree range
	void virtual isPlayerInRange(Vector2f playerPosition);

	int getHealAmount();

	int getFireRate();

	Time getLastShot();

	void setLastShot(Time time);

	bool getIsPlayerInRange();
};