#include "MimicBullet.h"
#include "TextureHolder.h"

// The constructor
MimicBullet::MimicBullet()
{
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/mimic-bullet.png"));
}

void MimicBullet::shoot(float startX, float startY,
	float targetX, float targetY, int multishotLevel)
{
	// Keep track of the bullet
	m_InFlight = true;
	m_Position.x = startX;
	m_Position.y = startY;

	// Calculate the gradient of the flight path
	float gradient = (startX - targetX) / (startY - targetY);

	// Any gradient less than 1 needs to be negative
	if (gradient < 0)
	{
		gradient *= -1;
	}

	// Calculate the ratio between x and y
	float ratioXY = m_BulletSpeed / (1 + gradient);

	// Set the "speed" horizontally and vertically
	m_BulletDistanceY = ratioXY;
	m_BulletDistanceX = ratioXY * gradient;

	// Point the bullet in the right direction
	if (targetX < startX)
	{
		m_BulletDistanceX *= -1;
	}
	if (targetY < startY)
	{
		m_BulletDistanceY *= -1;
	}

	// Set a max range of 1000 pixels
	float range = 1000;
	m_MinX = startX - range;
	m_MaxX = startX + range;
	m_MinY = startY - range;
	m_MaxY = startY + range;

	// Position the bullet ready to be drawn
	m_Sprite.setPosition(m_Position);

	if (multishotLevel >= 2) {
		// Calculate the angle between the player's current position and the target
		float playerDirection = atan2(targetY - startY, targetX - startX);

		// Calculate a random offset angle within the desired 180-degree arc
		float angleOffset = (rand() % 180 - 90) * (3.14159265359 / 180); // Random angle between -90 and 90 degrees

		// Calculate the new shooting angle within the 180-degree arc
		float shootingAngle = playerDirection + angleOffset;

		// Calculate the new target position based on the shooting angle and range
		float newTargetX = startX + cos(shootingAngle) * range; // Adjust range as needed
		float newTargetY = startY + sin(shootingAngle) * range; // Adjust range as needed

		// Call the shoot function for the bullet with the new target
		shoot(startX, startY, newTargetX, newTargetY, 1);
	}
}