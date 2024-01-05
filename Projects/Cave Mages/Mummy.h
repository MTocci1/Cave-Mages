#pragma once
#include "Enemy.h"

class Mummy : public Enemy
{
private:
	// Which directions is the spider currently moving in
	bool m_LeftPressed;
	bool m_RightPressed;
	bool m_UpPressed;
	bool m_DownPressed;

	float changeDirectionCooldown;

	float m_ChargeSpeed;
	bool m_isShooting;

	bool m_isIdle;

	void changeDirection();

	int m_FireRate;

	Time LastShot;

public:
	Mummy();

	// The overriden input handler for Spider
	void virtual update(float elapsedTime, bool playerFacingDirection, Vector2f playerPosition);

	// Check if the player is in enemy range
	void virtual isPlayerInRange(Vector2f playerPosition);

	void isMummyCloseToPlayer(Vector2f playerPosition);

	bool getIsIdle();

	bool getIsPlayerInRange();

	int getFireRate();

	Time getLastShot();

	void setLastShot(Time time);

	Vector2f getCenter();

	void IsOnWater(bool isOnWater, int& enemiesLeft);
};