#include "FireTurret.h"
#include "TextureHolder.h"
#include <random>
#include <iostream>


FireTurret::FireTurret(Vector2f position)
{
	// Associate a texture with the sprite
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/fire-turret.png"));
	m_Sprite.setScale(.5, .5);

	m_Position = position;

	m_Damage = 5;
	m_FireRate = 1;

	m_isSpawned = true;

	m_Sprite.setPosition(m_Position);

	m_Range = 500.0f;
}

// The overriden input handler for tree
void FireTurret::update(float elapsedTime, Vector2f targetPosition)
{
	if (m_isSpawned)
	{
		isEnemyInRange(targetPosition);

		m_Sprite.setPosition(m_Position);
	}

}

// Check if the player is in tree range
void FireTurret::isEnemyInRange(Vector2f enemyPosition)
{
	// m_range is the maximum distance for the player to be considered in range
	float range = m_Range;

	// Calculate the distance between spider and player using the distance formula
	float distance = sqrt(pow(enemyPosition.x - m_Position.x, 2) + pow(enemyPosition.y - m_Position.y, 2));

	// Check if the distance is within the specified range
	if (distance <= range) {
		m_isEnemyInRange = true;
	}
	else {
		m_isEnemyInRange = false;
	}
}

int FireTurret::getDamage()
{
	return m_Damage;
}

int FireTurret::getFireRate()
{
	return m_FireRate;
}

void FireTurret::setLastShot(Time time)
{
	LastShot = time;
}

Time FireTurret::getLastShot()
{
	return LastShot;
}

void FireTurret::setLastDelayedShot(Time time)
{
	LastDelayedShot = time;
}

Time FireTurret::getLastDelayedShot()
{
	return LastDelayedShot;
}

bool FireTurret::getIsPlayerInRange()
{
	return m_isEnemyInRange;
}

float FireTurret::getRange()
{
	return m_Range;
}