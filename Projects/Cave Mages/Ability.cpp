#include "Ability.h"
#include "TextureHolder.h"

// The constructor
Ability::Ability()
{
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/ability.png"));
}

void Ability::activate(float timeActive)
{
	// Keep track of the Ability
	m_Active = true;

	m_timeActive = timeActive;
}

void Ability::stop()
{
	m_Active = false;
}

bool Ability::isActive()
{
	return m_Active;
}

FloatRect Ability::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Sprite Ability::getSprite()
{
	return m_Sprite;
}

void Ability::update(float elapsedTime, float playerX, float playerY)
{
	// Update the time active
	m_timeActive -= elapsedTime;

	// Deactivate the ability
	if (m_timeActive <= 0.0f)
	{
		stop();
	}

	// Calculate the top-left corner based on the center and sprite size
	float halfWidth = m_Sprite.getLocalBounds().width / 2.0f;
	float halfHeight = m_Sprite.getLocalBounds().height / 2.0f;

	m_Position.x = playerX - halfWidth;
	m_Position.y = playerY - halfHeight;

	m_Sprite.setPosition(m_Position);
}