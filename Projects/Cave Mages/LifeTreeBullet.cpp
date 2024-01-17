#include "LifeTreeBullet.h"
#include "TextureHolder.h"

// The constructor
LifeTreeBullet::LifeTreeBullet(int healAmount)
{
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/life-tree-bullet.png"));

	m_HealAmount = healAmount;
	m_Speed = 200;
}

void LifeTreeBullet::shoot(float startX, float startY,
	float targetX, float targetY, int multishotLevel)
{
	// Keep track of the bullet
	m_Position.x = startX;
	m_Position.y = startY;

	m_InFlight = true;

	// Set a max range of 1000 pixels
	float range = 1000;
	m_MinX = startX - range;
	m_MaxX = startX + range;
	m_MinY = startY - range;
	m_MaxY = startY + range;

	m_Sprite.setPosition(m_Position);
	
}

void LifeTreeBullet::followPlayer(Vector2f playerPosition, float elapsedTime)
{
	float playerX = playerPosition.x;
	float playerY = playerPosition.y;

	//Chase the player
	// Calculate direction to player
	float directionX = playerX - m_Position.x;
	float directionY = playerY - m_Position.y;

	// Normalize the direction vector
	float length = sqrt(directionX * directionX + directionY * directionY);
	directionX /= length;
	directionY /= length;

	// Move towards the player
	m_Position.x += m_Speed * elapsedTime * directionX;
	m_Position.y += m_Speed * elapsedTime * directionY;

	// Has the bullet gone out of range?
	if (m_Position.x < m_MinX || m_Position.x > m_MaxX ||
		m_Position.y < m_MinY || m_Position.y > m_MaxY)
	{
		m_InFlight = false;
	}

	// Move the bullet
	m_Sprite.setPosition(m_Position);
}

int LifeTreeBullet::getHealAmount()
{
	return m_HealAmount;
}