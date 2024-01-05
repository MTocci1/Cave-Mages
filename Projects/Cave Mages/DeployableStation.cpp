#include "DeployableStation.h"
#include "TextureHolder.h"
#include <random>

DeployableStation::DeployableStation()
{
	// Associate a texture with the sprite
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/deployable-station.png"));

	// Load the font
	m_Font.loadFromFile("fonts/impact.ttf");

	// Text when player touches deployable
	m_Text.setFont(m_Font);
	m_Text.setCharacterSize(25);
	m_Text.setFillColor(Color::White);
	m_Text.setString("");

	m_UpgradeCost = 600;

	m_isSpawned = true;
}

void DeployableStation::spawn(IntRect arena, Vector2f resolution, int tileSize)
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

void DeployableStation::isPlayerInRange(Vector2f playerPosition)
{
	// m_range is the maximum distance for the player to be considered in range
	float range = 300.0f;

	// Calculate the distance between deployable and player using the distance formula
	float distance = sqrt(pow(playerPosition.x - getCenter().x, 2) + pow(playerPosition.y - getCenter().y, 2));

	// Check if the distance is within the specified range
	if (distance <= range) {
		showText();
	}
	else {
		hideText();
	}
}

void DeployableStation::showText()
{
	FloatRect textRect = m_Text.getLocalBounds();
	m_Text.setPosition(
		getCenter().x - textRect.width / 2,
		getCenter().y - textRect.height / 2
	);
	String cost = std::to_string(m_UpgradeCost);
	m_Text.setString("Press [F] To Upgrade (" + cost + " XP)");
	
}

void DeployableStation::hideText()
{
	m_Text.setString("");
}

Text DeployableStation::getText()
{
	return m_Text;
}

int DeployableStation::getUpgradeCost()
{
	return m_UpgradeCost;
}