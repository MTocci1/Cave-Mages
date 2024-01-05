#include "Deployable.h"
#include <random>
#include <iostream>

FloatRect Deployable::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Vector2f Deployable::getCenter()
{
	return Vector2f(
		m_Position.x + m_Sprite.getGlobalBounds().width / 2,
		m_Position.y + m_Sprite.getGlobalBounds().height / 2
	);
}

Sprite Deployable::getSprite()
{
	return m_Sprite;
}

bool Deployable::getIsSpawned()
{
	return m_isSpawned;
}
