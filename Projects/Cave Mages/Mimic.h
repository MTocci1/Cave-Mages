#pragma once
#include "Enemy.h"

class Mimic : public Enemy
{
private:
	// Which directions is the spider currently moving in
	bool m_LeftPressed;
	bool m_RightPressed;
	bool m_UpPressed;
	bool m_DownPressed;

	float changeDirectionCooldown;

	void changeDirection();

	float m_FireRate;

	float m_abilityCooldown;
	float m_abilityActiveTime;
	int m_abilityDamage;

	int m_DodgeSpeed;
	int m_DodgeSpeedOnWater;

public:
	Mimic();

	// The overriden input handler for Spider
	void virtual update(float elapsedTime, bool playerFacingDirection, Vector2f playerPosition);

	// Check if the player is in enemy range
	void virtual isPlayerInRange(Vector2f playerPosition);

	void setFacingDirection(bool isAimingRight);

	Vector2f getCenter();

	void setup(float playerFireRate, int playerSpeed, int playerDamage, float playerAbilityCooldown, float playerAbilityActiveTime, 
		int playerAbilityDamage, IntRect arena, Vector2f resolution, int tileSize);
};