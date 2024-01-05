#pragma once
#include "Bullet.h"

class MummyBullet : public Bullet
{
private:
	float m_rotateSpeed;

public:
	MummyBullet();

	void virtual shoot(float startX, float startY, float xTarget, float yTarget, int multishotLevel);

	void rotate(float elapsedTime);
};