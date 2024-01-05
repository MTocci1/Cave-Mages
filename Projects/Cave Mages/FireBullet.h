#pragma once
#include "Bullet.h"

class FireBullet : public Bullet 
{
public:
	FireBullet();

	void virtual shoot(float startX, float startY, float xTarget, float yTarget, int multishotLevel);
};