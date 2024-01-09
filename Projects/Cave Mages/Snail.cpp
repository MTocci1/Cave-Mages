#include "Snail.h"
#include "TextureHolder.h"
#include <random>
#include <iostream>

Snail::Snail()
{
	// Associate a texture with the sprite
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/snail.png"));
	m_Sprite.setScale(.10, .10);

	m_isAlive = true;

	m_Speed = 20;
	m_SpeedOnWater = m_Speed / 2;
}

void Snail::spawn(IntRect arena, Vector2f resolution, int tileSize)
{
	// Copy the details of the arena to the player's m_Arena
	m_Arena.left = arena.left;
	m_Arena.width = arena.width;
	m_Arena.top = arena.top;
	m_Arena.height = arena.height;

	// Remember how big the tiles are in this arena
	m_TileSize = tileSize;

	// Store the resolution for future use
	m_Resolution.x = resolution.x;
	m_Resolution.y = resolution.y;

	// Calculate the center of the arena
	int centerX = m_Arena.left + m_Arena.width / 2;
	int centerY = m_Arena.top + m_Arena.height / 2;

	// Ensure Enemy do not spawn in center (where player spawns)
	int centerRangeX = m_Arena.width / 8;
	int centerRangeY = m_Arena.height / 8;

	// Create random number generators
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distX(m_Arena.left, m_Arena.left + m_Arena.width - tileSize);
	std::uniform_int_distribution<int> distY(m_Arena.top, m_Arena.top + m_Arena.height - tileSize);

	// Spawn enemies randomly outside the center range
	int x, y;
	do {
		x = distX(gen);
		y = distY(gen);
	} while (abs(x - centerX) < centerRangeX && abs(y - centerY) < centerRangeY);

	m_Position.x = x;
	m_Position.y = y;
	m_Sprite.setPosition(m_Position);
}

void Snail::update(float elapsedTime, bool playerFacingDirection, Vector2f playerPosition)
{
	if (m_isAlive) {
		m_SpeedOnWater = m_Speed / 2;

		float playerX = playerPosition.x;
		float playerY = playerPosition.y;

		// Chase the Player
		if (playerX > m_Position.x)
		{
			if (m_isOnWater) {
				m_Position.x = m_Position.x + m_SpeedOnWater * elapsedTime;
			}
			else {
				m_Position.x = m_Position.x + m_Speed * elapsedTime;
			}

			setFacingDirection(false);
		}

		if ((playerX > m_Position.x) || (playerX < m_Position.x)) {
			if (playerY > m_Position.y)
			{
				if (m_isOnWater) {
					m_Position.y = m_Position.y + m_SpeedOnWater * elapsedTime;
				}
				else {
					m_Position.y = m_Position.y + m_Speed * elapsedTime;
				}
			}
		}

		if (playerX < m_Position.x)
		{
			if (m_isOnWater) {
				m_Position.x = m_Position.x - m_SpeedOnWater * elapsedTime;
			}
			else {
				m_Position.x = m_Position.x - m_Speed * elapsedTime;
			}

			setFacingDirection(true);
		}

		if ((playerX > m_Position.x) || (playerX < m_Position.x)) {
			if (playerY < m_Position.y)
			{
				if (m_isOnWater) {
					m_Position.y = m_Position.y - m_SpeedOnWater * elapsedTime;
				}
				else {
					m_Position.y = m_Position.y - m_Speed * elapsedTime;
				}
			}
		}

		// Keep the enemy in the arena
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

FloatRect Snail::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Vector2f Snail::getCenter()
{
	return Vector2f(
		m_Position.x + m_Sprite.getGlobalBounds().width / 2,
		m_Position.y + m_Sprite.getGlobalBounds().height / 2
	);
}

Sprite Snail::getSprite()
{
	return m_Sprite;
}

void Snail::cancelMovement() {
	m_Sprite.setPosition(prevPosition);
	m_Position = prevPosition;
}

void Snail::setIsOnWater(bool isSpiderOnWater)
{
	m_isOnWater = isSpiderOnWater;
}

bool Snail::getFacingDirection()
{
	return m_facingLeft;
}

void Snail::setFacingDirection(bool isAimingRight)
{
	if (isAimingRight)
	{
		m_facingRight = true;
		m_facingLeft = false;

		m_Sprite.setScale(.10, .10);

		m_Sprite.setOrigin(0, 0);


	}
	else {
		m_facingRight = false;
		m_facingLeft = true;

		m_Sprite.setScale(-.10, .10);

		m_Sprite.setOrigin(m_Sprite.getLocalBounds().width, 0);
	}
}