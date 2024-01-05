#include "LifeTree.h"
#include "TextureHolder.h"
#include <random>
#include <iostream>


LifeTree::LifeTree(Vector2f position)
{
	// Associate a texture with the sprite
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/tree-of-life.png"));
	m_Sprite.setScale(.5, .5);

	m_Position = position;

	m_HealAmount = 5;
	m_FireRate = 1;

	m_isSpawned = true;

	m_Sprite.setPosition(m_Position);
}

// The overriden input handler for tree
void LifeTree::update(float elapsedTime, Vector2f targetPosition)
{
	if (m_isSpawned)
	{
		isPlayerInRange(targetPosition);
		
		m_Sprite.setPosition(m_Position);
	}

}

// Check if the player is in tree range
void LifeTree::isPlayerInRange(Vector2f playerPosition)
{
	// m_range is the maximum distance for the player to be considered in range
	float range = 500.0f;

	// Calculate the distance between spider and player using the distance formula
	float distance = sqrt(pow(playerPosition.x - m_Position.x, 2) + pow(playerPosition.y - m_Position.y, 2));

	// Check if the distance is within the specified range
	if (distance <= range) {
		m_isPlayerInRange = true;
	}
	else {
		m_isPlayerInRange = false;
	}
}

int LifeTree::getHealAmount()
{
	return m_HealAmount;
}

int LifeTree::getFireRate()
{
	return m_FireRate;
}

void LifeTree::setLastShot(Time time)
{
	LastShot = time;
}

Time LifeTree::getLastShot()
{
	return LastShot;
}

bool LifeTree::getIsPlayerInRange()
{
	return m_isPlayerInRange;
}