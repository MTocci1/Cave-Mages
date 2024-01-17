#include "Slime.h"
#include "TextureHolder.h"
#include <random>
#include <iostream>

Slime::Slime()
{
	// Associate a texture with the sprite
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/slime.png"));
	m_Sprite.setScale(.25, .25);

	// Load the font
	m_Font.loadFromFile("fonts/impact.ttf");

	// when Paused
	m_DamageText.setFont(m_Font);
	m_DamageText.setCharacterSize(35);
	m_DamageText.setFillColor(Color::Cyan);
	m_DamageText.setString("");

	textTimer = 0.0f;

	m_TotalDamage = 0;

	m_isAlive = true;

	m_Speed = 200;
	m_SpeedOnWater = m_Speed / 2;
	m_SpeedOnRock = m_Speed / 2;

	m_Health = 20;
	m_Damage = 10;

	m_Level = 1;

}

void Slime::eatenEnemy()
{
	m_Level += 1;
	m_Health += 10;
}

void Slime::touchedOtherSlime(int level, int health)
{
	m_Health += health;
	m_Level += level;
}

int Slime::getLevel()
{
	return m_Level;
}

void Slime::isPlayerInRange(Vector2f playerPosition)
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


void Slime::update(float elapsedTime, bool playerFacingDirection, Vector2f playerPosition)
{
	if (m_isAlive) {
		
		m_SpeedOnWater = m_Speed / 2;
		m_SpeedOnRock = m_Speed / 2;

		float playerX = playerPosition.x;
		float playerY = playerPosition.y;

		// Count the number of keys pressed
		int keysPressedCount = 0;
		if (m_LeftPressed || m_RightPressed) {
			keysPressedCount++;
		}
		if (m_UpPressed || m_DownPressed) {
			keysPressedCount++;
		}
		// Update the factor based on the number of keys pressed
		float factor = 1.0f / sqrt(keysPressedCount);

		// Calculate direction to player
		float directionX = playerX - m_Position.x;
		float directionY = playerY - m_Position.y;

		// Normalize the direction vector
		float length = sqrt(directionX * directionX + directionY * directionY);
		directionX /= length;
		directionY /= length;

		// Adjust movement flags based on direction
		m_RightPressed = (directionX > 0);
		m_LeftPressed = (directionX < 0);
		m_UpPressed = (directionY > 0);
		m_DownPressed = (directionY < 0);

		// Move towards the player
		if (m_RightPressed || m_LeftPressed || m_UpPressed || m_DownPressed) {
			float speed;
			if (m_isOnRock) {
				speed = m_SpeedOnRock;
			}
			else if (m_isOnWater) {
				speed = m_SpeedOnWater;
			}
			else {
				speed = m_Speed;
			}
			m_Position.x += speed * elapsedTime * factor * directionX;
			m_Position.y += speed * elapsedTime * factor * directionY;
		}

		// Adjust facing direction based on movement
		if (directionX > 0) {
			setFacingDirection(false);
		}
		else {
			setFacingDirection(true);
		}

		m_Damage = 5 + (5 * m_Level);
		m_Speed = 200 - (5 * m_Level);

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

		// Update the damage text position
		FloatRect textRect = m_DamageText.getLocalBounds();
		m_DamageText.setPosition(
			getCenter().x - textRect.width / 2,
			getCenter().y - (textRect.height / 2) - 45
		);

		m_lastHitByAbility -= elapsedTime;
		m_lastHitBySlime -= elapsedTime;
	}

	// Only show damage text for a limited time
	textTimer -= elapsedTime;
	if (textTimer < 0.0)
	{
		m_TotalDamage = 0;
		m_DamageText.setString("");
	}
}

void Slime::setIsOnRock(bool isOnRock)
{
	m_isOnRock = isOnRock;
}

void Slime::setFacingDirection(bool isAimingRight)
{
	if (isAimingRight)
	{
		m_facingRight = true;
		m_facingLeft = false;

		m_Sprite.setScale(.25 + (.05 * m_Level), .25 + (.05 * m_Level));

		m_Sprite.setOrigin(0, 0);


	}
	else {
		m_facingRight = false;
		m_facingLeft = true;

		m_Sprite.setScale(-(.25 + (.05 * m_Level)), .25 + (.05 * m_Level));

		m_Sprite.setOrigin(m_Sprite.getLocalBounds().width, 0);
	}
}