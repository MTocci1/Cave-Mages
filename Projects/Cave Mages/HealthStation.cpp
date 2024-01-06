#include "HealthStation.h"
#include "TextureHolder.h"
#include <random>

HealthStation::HealthStation()
{
	// Associate a texture with the sprite
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/health-station.png"));
	m_Sprite.setScale(.5, .5);
}

void HealthStation::spawn(IntRect arena, Vector2f resolution, int tileSize)
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

	// Make sure they don't spawn partially out of the arena
	if (m_Position.x > m_Arena.width - 250) {
		m_Position.x = m_Arena.width - 250;
	}

	if (m_Position.y > m_Arena.height - 250) {
		m_Position.y = m_Arena.height - 250;
	}


	m_Sprite.setPosition(m_Position);
}