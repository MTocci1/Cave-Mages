#include "Mummy.h"
#include "TextureHolder.h"
#include <random>
#include <iostream>

Mummy::Mummy()
{
	// Associate a texture with the sprite
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/mummy.png"));
	m_Sprite.setScale(.4, .4);

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

	m_Speed = 50;
	m_SpeedOnWater = m_Speed / 2;
	m_ChargeSpeed = 200;

	m_Health = 100;
	m_Damage = 0;

	changeDirectionCooldown = 4.0f;

	m_FireRate = 1;
}

void Mummy::changeDirection()
{
	if (changeDirectionCooldown == 4.0)
	{
		// Random number generation for direction
		std::random_device rdDirection;
		std::mt19937 genDirection(rdDirection());
		std::uniform_int_distribution<int> distribDirection(1, 4);

		int direction = distribDirection(genDirection);

		if (direction == 1)
		{
			m_LeftPressed = true;
			m_RightPressed = false;
			m_DownPressed = false;
			m_UpPressed = false;
		}
		if (direction == 2)
		{
			m_LeftPressed = false;
			m_RightPressed = true;
			m_DownPressed = false;
			m_UpPressed = false;
		}
		if (direction == 3)
		{
			m_LeftPressed = false;
			m_RightPressed = false;
			m_DownPressed = true;
			m_UpPressed = false;
		}
		if (direction == 4)
		{
			m_LeftPressed = false;
			m_RightPressed = false;
			m_DownPressed = false;
			m_UpPressed = true;
		}
	}
}

void Mummy::isPlayerInRange(Vector2f playerPosition)
{
	// m_range is the maximum distance for the player to be considered in range
	float range = 700.0f;

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

void Mummy::isMummyCloseToPlayer(Vector2f playerPosition)
{
	// m_range is the maximum distance for the player to be considered in range
	float range = 300.0f;

	// Calculate the distance between spider and player using the distance formula
	float distance = sqrt(pow(playerPosition.x - m_Position.x, 2) + pow(playerPosition.y - m_Position.y, 2));

	// Check if the distance is within the specified range
	if (distance <= range) {
		m_isIdle = true;
	}
	else {
		m_isIdle = false;
	}
}

void Mummy::update(float elapsedTime, bool playerFacingDirection, Vector2f playerPosition)
{
	if (m_isAlive) {

		isPlayerInRange(playerPosition);

		isMummyCloseToPlayer(playerPosition);

		if (!m_isPlayerInRange)
		{
			changeDirection();

			changeDirectionCooldown -= elapsedTime;
			if (changeDirectionCooldown <= 0.0)
			{
				changeDirectionCooldown = 4.0;
			}

			// Move the Mummy
			if (m_LeftPressed)
			{
				m_Position.x -= m_Speed * elapsedTime;
			}
			if (m_RightPressed)
			{
				m_Position.x += m_Speed * elapsedTime;
			}
			if (m_DownPressed)
			{
				m_Position.y += m_Speed * elapsedTime;
			}
			if (m_UpPressed)
			{
				m_Position.y -= m_Speed * elapsedTime;
			}
		}
		else if (m_isPlayerInRange && !m_isIdle)
		{

			float playerX = playerPosition.x;
			float playerY = playerPosition.y;

			// Chase the Player
			if (playerX > m_Position.x)
			{
				m_Position.x = m_Position.x + m_ChargeSpeed * elapsedTime;
			}

			if ((playerX > m_Position.x) || (playerX < m_Position.x)) {
				if (playerY > m_Position.y)
				{
					m_Position.y = m_Position.y + m_ChargeSpeed * elapsedTime;
				}
			}

			if (playerX < m_Position.x)
			{
				m_Position.x = m_Position.x - m_ChargeSpeed * elapsedTime;
			}

			if ((playerX > m_Position.x) || (playerX < m_Position.x)) {
				if (playerY < m_Position.y)
				{
					m_Position.y = m_Position.y - m_ChargeSpeed * elapsedTime;
				}
			}
		}
		else if (m_isIdle) 
		{

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

bool Mummy::getIsIdle()
{
	return m_isIdle;
}

bool Mummy::getIsPlayerInRange()
{
	return m_isPlayerInRange;
}

int Mummy::getFireRate()
{
	return m_FireRate;
}

void Mummy::setLastShot(Time time)
{
	LastShot = time;
}

Time Mummy::getLastShot()
{
	return LastShot;
}

Vector2f Mummy::getCenter()
{
	return Vector2f(
		m_Position.x + m_Sprite.getGlobalBounds().width / 2,
		m_Position.y + m_Sprite.getGlobalBounds().height / 2
	);
}

void Mummy::IsOnWater(bool isOnWater, int &enemiesLeft)
{
	if (isOnWater)
	{
		hit(100, enemiesLeft);
	}
}