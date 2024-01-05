#pragma once
#include "Enemy.h"

class Slime : public Enemy
{
private:
	// Which directions is the spider currently moving in
	bool m_LeftPressed;
	bool m_RightPressed;
	bool m_UpPressed;
	bool m_DownPressed;

	int m_Level;

	int m_SpeedOnRock;

	bool m_isOnRock;

public:
	Slime();

	// The overriden input handler for Spider
	void virtual update(float elapsedTime, bool playerFacingDirection, Vector2f playerPosition);

	int getLevel();

	// Check if the player is in enemy range
	void virtual isPlayerInRange(Vector2f playerPosition);

	void eatenEnemy();

	void touchedOtherSlime(int level, int health);

	void setIsOnRock(bool isOnRock);
};