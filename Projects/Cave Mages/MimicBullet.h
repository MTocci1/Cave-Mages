#pragma once
#include "Bullet.h"

class MimicBullet : public Bullet
{
public:
	MimicBullet();

	void virtual shoot(float startX, float startY, float xTarget, float yTarget, int multishotLevel);
};