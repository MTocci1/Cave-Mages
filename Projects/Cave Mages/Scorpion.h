#pragma once
#include "Enemy.h"

class Scorpion : public Enemy
{
private:
	// Which directions is the spider currently moving in
	bool m_LeftPressed;
	bool m_RightPressed;
	bool m_UpPressed;
	bool m_DownPressed;

	float changeDirectionCooldown;

	float m_ChargeSpeed;
	float m_ChargeSpeedOnWater;
	float m_FleeSpeed;
	float m_FleeSpeedOnWater;

	bool m_isFleeing = false;
	//How long does the scorpion flee
	float m_FleeTime;

	void changeDirection();

public:
	Scorpion();

	// The overriden input handler for Spider
	void virtual update(float elapsedTime, bool playerFacingDirection, Vector2f playerPosition);

	// Check if the player is in enemy range
	void virtual isPlayerInRange(Vector2f playerPosition);

	void setFacingDirection(bool isAimingRight);

	void activateFlee();
};