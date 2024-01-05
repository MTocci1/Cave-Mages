#include "Obstacle.h"

FloatRect Obstacle::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Sprite Obstacle::getSprite()
{
	return m_Sprite;
}

bool Obstacle::isSpawned()
{
	return m_Spawned;
}

FloatRect Obstacle::getCollider() const
{
	return m_Sprite.getGlobalBounds();
}

void Obstacle::update(float elapsedTime)
{
	m_Sprite.setPosition(m_Position);
}

Vector2f Obstacle::getCenter()
{
	return Vector2f(
		m_Position.x + m_Sprite.getGlobalBounds().width / 2,
		m_Position.y + m_Sprite.getGlobalBounds().height / 2
	);
}

void Obstacle::despawn()
{
	m_Spawned = false;
}