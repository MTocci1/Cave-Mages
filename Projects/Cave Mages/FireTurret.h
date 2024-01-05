#pragma once
#include "Deployable.h"

class FireTurret : public Deployable
{
private:
	int m_Damage;

	bool m_isEnemyInRange;

	int m_FireRate;
	Time LastShot;
	Time LastDelayedShot;

	float m_Range;

public:
	FireTurret(Vector2f position);

	// The overriden input handler for tree
	void virtual update(float elapsedTime, Vector2f targetPosition);

	// Check if the player is in tree range
	void virtual isEnemyInRange(Vector2f enemyPosition);

	int getDamage();

	int getFireRate();

	Time getLastShot();

	void setLastShot(Time time);

	Time getLastDelayedShot();

	void setLastDelayedShot(Time time);

	bool getIsPlayerInRange();

	float getRange();
};