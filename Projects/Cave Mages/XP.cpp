#include "XP.h"
#include <random>
#include <iostream>

FloatRect XP::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Sprite XP::getSprite()
{
	return m_Sprite;
}

int XP::getValue()
{
	return m_Value;
}

void XP::touchedByPlayer()
{
	m_isSpawned = false;
}

void XP::cancelMovement() {
	m_Sprite.setPosition(prevPosition);
	m_Position = prevPosition;
}

bool XP::getIsSpawned()
{
	return m_isSpawned;
}
