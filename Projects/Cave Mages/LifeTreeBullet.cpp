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
	m_Sprite.setPosition(m_Position);
	
}

void LifeTreeBullet::followPlayer(Vector2f playerPosition, float elapsedTime)
{
	float playerX = playerPosition.x;
	float playerY = playerPosition.y;

	// Chase the Player
	if (playerX > m_Position.x)
	{
		m_Position.x = m_Position.x + m_Speed * elapsedTime;
	}

	if ((playerX > m_Position.x) || (playerX < m_Position.x)) {
		if (playerY > m_Position.y)
		{
			m_Position.y = m_Position.y + m_Speed * elapsedTime;
		}
	}

	if (playerX < m_Position.x)
	{
		m_Position.x = m_Position.x - m_Speed * elapsedTime;
	}

	if ((playerX > m_Position.x) || (playerX < m_Position.x)) {
		if (playerY < m_Position.y)
		{
			m_Position.y = m_Position.y - m_Speed * elapsedTime;
		}
	}

	// Move the bullet
	m_Sprite.setPosition(m_Position);
}

int LifeTreeBullet::getHealAmount()
{
	return m_HealAmount;
}