#include "Mummy.h"
#include "TextureHolder.h"
#include <random>
#include <iostream>

Mummy::Mummy()
{
	// Associate a texture with the sprite
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/mummy.png"));
	m_Sprite.setScale(.35, .35);

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

	m_Speed = 100;
	m_SpeedOnWater = m_Speed / 2;
	m_ChargeSpeed = 300;

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
				m_Position.x -= m_Speed * elapsedTime * factor;
			}
			if (m_RightPressed)
			{
				m_Position.x += m_Speed * elapsedTime * factor;
			}
			if (m_DownPressed)
			{
				m_Position.y += m_Speed * elapsedTime * factor;
			}
			if (m_UpPressed)
			{
				m_Position.y -= m_Speed * elapsedTime * factor;
			}
		}
		else if (m_isPlayerInRange && !m_isIdle)
		{

			// Chase the Player
			float playerX = playerPosition.x;
			float playerY = playerPosition.y;

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
			m_Position.x += m_ChargeSpeed * elapsedTime * factor * directionX;
			m_Position.y += m_ChargeSpeed * elapsedTime * factor * directionY;

			// Adjust facing direction based on movement
			if (directionX > 0) {
				setFacingDirection(false);
			}
			else {
				setFacingDirection(true);
			}
		}
		else if (m_isIdle) 
		{
			float playerX = playerPosition.x;

			// Face the Player
			if (playerX > m_Position.x)
			{
				setFacingDirection(true);
			}
			if (playerX < m_Position.x)
			{
				setFacingDirection(false);
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

void Mummy::setFacingDirection(bool isAimingRight)
{
	if (isAimingRight)
	{
		m_facingRight = true;
		m_facingLeft = false;

		m_Sprite.setScale(.35, .35);

		m_Sprite.setOrigin(0, 0);


	}
	else {
		m_facingRight = false;
		m_facingLeft = true;

		m_Sprite.setScale(-.35, .35);

		m_Sprite.setOrigin(m_Sprite.getLocalBounds().width, 0);
	}
}