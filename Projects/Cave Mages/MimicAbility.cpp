#include "MimicAbility.h"
#include "TextureHolder.h"

// The constructor
MimicAbility::MimicAbility()
{
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/mimic-ability.png"));
}

void MimicAbility::activate(float timeActive)
{
	// Keep track of the Ability
	m_Active = true;

	m_timeActive = timeActive;
}

void MimicAbility::stop()
{
	m_Active = false;
}

bool MimicAbility::isActive()
{
	return m_Active;
}

FloatRect MimicAbility::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Sprite MimicAbility::getSprite()
{
	return m_Sprite;
}

void MimicAbility::update(float elapsedTime, float mimicX, float mimicY)
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

	m_Position.x = mimicX - halfWidth;
	m_Position.y = mimicY - halfHeight;

	m_Sprite.setPosition(m_Position);
}