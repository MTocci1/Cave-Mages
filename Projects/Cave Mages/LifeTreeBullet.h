#pragma once
#include "Bullet.h"

class LifeTreeBullet : public Bullet
{
private:
	int m_HealAmount;

	int m_Speed;

public:
	LifeTreeBullet(int healAmount);

	void virtual shoot(float startX, float startY, float xTarget, float yTarget, int multishotLevel);

	void followPlayer(Vector2f playerPosition, float elapsedTime);

	int getHealAmount();
};