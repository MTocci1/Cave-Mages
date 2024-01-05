#pragma once
#include "Bullet.h"

class FireTurretBullet : public Bullet
{
private:
	int m_Damage;

	int m_Speed;

public:
	FireTurretBullet(int damage);

	void virtual shoot(float startX, float startY, float xTarget, float yTarget, int multishotLevel);

	int getDamage();
};