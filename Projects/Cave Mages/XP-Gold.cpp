#include "XP-Gold.h"
#include "TextureHolder.h"
#include <random>
#include <iostream>

Gold::Gold(float positionX, float positionY, IntRect arena, Vector2f resolution, int tileSize)
{
	m_Position.x = positionX;
	m_Position.y = positionY;

	// Associate a texture with the sprite
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/xp-gold.png"));
	m_Sprite.setScale(.10, .10);

	m_Value = 50;

	m_Arena = arena;
	m_Resolution = resolution;
	m_TileSize = tileSize;

	m_isSpawned = true;

	m_Speed = 50;

	m_Sprite.setPosition(m_Position);
}

void Gold::isPlayerInRange(Vector2f playerPosition)
{
	// m_range is the maximum distance for the player to be considered in range
	float range = 300.0f;

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

void Gold::update(float elapsedTime, Vector2f playerPosition)
{
	if (m_isSpawned) {

		isPlayerInRange(playerPosition);

		if (m_isPlayerInRange)
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
		}

		// Keep the XP in the arena
		if (m_Position.x > m_Arena.width - m_TileSize)
		{
			m_Position.x = m_Arena.width - m_TileSize;
		}
		if (m_Position.x < m_Arena.left)
		{
			m_Position.x = m_Arena.left;
		}
		if (m_Position.y > m_Arena.height - m_TileSize)
		{
			m_Position.y = m_Arena.height - m_TileSize;
		}
		if (m_Position.y < m_Arena.top)
		{
			m_Position.y = m_Arena.top;
		}

		prevPosition = m_Sprite.getPosition();
		Vector2f newPosition = prevPosition + Vector2f(elapsedTime * m_Speed, elapsedTime * m_Speed);

		m_Sprite.setPosition(m_Position);
	}
}