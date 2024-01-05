#include "Dummy.h"
#include "TextureHolder.h"
#include <random>


Dummy::Dummy()
{
	// Associate a texture with the sprite
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/dummy.png"));
	m_Sprite.setScale(.75, .75);

	// Move the sprite in to position
	m_Sprite.setPosition(m_Position);

	// Load the font
	m_Font.loadFromFile("fonts/impact.ttf");

	// when Paused
	m_DamageText.setFont(m_Font);
	m_DamageText.setCharacterSize(35);
	m_DamageText.setFillColor(Color::Cyan);
	m_DamageText.setString("");

	textTimer = 0.0f;

	m_TotalDamage = 0;

	m_TotalGameDamage = 0;
}

void Dummy::spawn(IntRect arena, Vector2f resolution, int tileSize)
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

void Dummy::update(float elapsedTime)
{
	m_Sprite.setPosition(m_Position);

	// Only show damage text for a limited time
	textTimer -= elapsedTime;
	if (textTimer < 0.0) 
	{
		m_TotalDamage = 0;
		m_DamageText.setString("");
	}

	m_lastHitByAbility -= elapsedTime;
}

FloatRect Dummy::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Vector2f Dummy::getCenter()
{
	return Vector2f(
		m_Position.x + m_Sprite.getGlobalBounds().width / 2,
		m_Position.y + m_Sprite.getGlobalBounds().height / 2
	);
}

Sprite Dummy::getSprite()
{
	return m_Sprite;
}

Text Dummy::getText()
{
	return m_DamageText;
}

void Dummy::hit(int damage)
{
	m_TotalDamage += damage;
	m_TotalGameDamage += damage;
	textTimer = 2.0f;
	m_DamageText.setString(std::to_string(m_TotalDamage));

	// Update the position of m_DamageText to align with the center of the Dummy
	FloatRect textRect = m_DamageText.getLocalBounds();
	m_DamageText.setPosition(
		getCenter().x - textRect.width / 2,
		getCenter().y - (textRect.height / 2) -85
	);
}

void Dummy::hitByAbility(int damage)
{
	if (m_lastHitByAbility < 0.0)
	{
		m_lastHitByAbility = 1.0;
		hit(damage);
	}
}


bool Dummy::isSpawned()
{
	return m_Spawned;
}

void Dummy::setSpawn(bool spawn)
{
	m_Spawned = spawn;
}