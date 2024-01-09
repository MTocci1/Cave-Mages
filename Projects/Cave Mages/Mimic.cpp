#include "Mimic.h"
#include "TextureHolder.h"
#include <random>
#include <iostream>

Mimic::Mimic()
{
	// Associate a texture with the sprite
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/mimic.png"));
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

	m_Health = 200;

	changeDirectionCooldown = .5f;
}

void Mimic::setup(float playerFireRate, int playerSpeed, int playerDamage, float playerAbilityCooldown, float playerAbilityActiveTime, 
	int playerAbilityDamage, IntRect arena, Vector2f resolution, int tileSize)
{
	m_isAlive = true;

	m_FireRate = playerFireRate;
	m_Speed = playerSpeed;
	m_DodgeSpeed = playerSpeed / 2;
	m_Damage = playerDamage;
	m_abilityCooldown = playerAbilityCooldown;
	m_abilityActiveTime = playerAbilityActiveTime;
	m_abilityDamage = playerAbilityDamage;

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

	m_Position.x = m_Arena.width / 2;
	m_Position.y = m_Arena.height / 4;

	m_Sprite.setPosition(m_Position);

}

void Mimic::changeDirection()
{
	if (changeDirectionCooldown == .5)
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

void Mimic::isPlayerInRange(Vector2f playerPosition)
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

void Mimic::update(float elapsedTime, bool playerFacingDirection, Vector2f playerPosition)
{
	if (m_isAlive) {

		isPlayerInRange(playerPosition);

		if (m_isPlayerInRange)
		{
			m_DodgeSpeedOnWater = m_DodgeSpeed / 2;

			changeDirection();

			changeDirectionCooldown -= elapsedTime;
			if (changeDirectionCooldown <= 0.0)
			{
				changeDirectionCooldown = .5;
			}

			// Move the mimic
			if (m_LeftPressed)
			{
				if (m_isOnWater) {
					m_Position.x -= m_DodgeSpeedOnWater * elapsedTime;
				}
				else {
					m_Position.x -= m_DodgeSpeed * elapsedTime;
				}
			}
			if (m_RightPressed)
			{
				if (m_isOnWater) {
					m_Position.x += m_DodgeSpeedOnWater * elapsedTime;
				}
				else {
					m_Position.x += m_DodgeSpeed * elapsedTime;
				}
			}
			if (m_DownPressed)
			{
				if (m_isOnWater) {
					m_Position.y += m_DodgeSpeedOnWater * elapsedTime;
				}
				else {
					m_Position.y += m_DodgeSpeed * elapsedTime;
				}
			}
			if (m_UpPressed)
			{
				if (m_isOnWater) {
					m_Position.y -= m_DodgeSpeedOnWater * elapsedTime;
				}
				else {
					m_Position.y -= m_DodgeSpeed * elapsedTime;
				}
			}
		}
		else
		{
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
			getCenter().y - (textRect.height / 2) - 65
		);

		m_lastHitByAbility -= elapsedTime;
	}

	// Only show damage text for a limited time
	textTimer -= elapsedTime;
	if (textTimer < 0.0)
	{
		m_TotalDamage = 0;
		m_DamageText.setString("");
	}
}

Vector2f Mimic::getCenter()
{
	return Vector2f(
		m_Position.x + m_Sprite.getGlobalBounds().width / 2,
		m_Position.y + m_Sprite.getGlobalBounds().height / 2
	);
}

void Mimic::setFacingDirection(bool isAimingRight)
{
	if (isAimingRight)
	{
		m_facingRight = true;
		m_facingLeft = false;

		m_Sprite.setScale(.25, .25);

		m_Sprite.setOrigin(0, 0);


	}
	else {
		m_facingRight = false;
		m_facingLeft = true;

		m_Sprite.setScale(-.25, .25);

		m_Sprite.setOrigin(m_Sprite.getLocalBounds().width, 0);
	}
}