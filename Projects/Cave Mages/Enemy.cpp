#include "Enemy.h"
#include <random>
#include <iostream>

void Enemy::spawn(IntRect arena, Vector2f resolution, int tileSize)
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

FloatRect Enemy::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Vector2f Enemy::getCenter()
{
	return Vector2f(
		m_Position.x + m_Sprite.getGlobalBounds().width / 2,
		m_Position.y + m_Sprite.getGlobalBounds().height / 2
	);
}

Sprite Enemy::getSprite()
{
	return m_Sprite;
}

int Enemy::getDamage()
{
	return m_Damage;
}

int Enemy::getHealth()
{
	return m_Health;
}

Text Enemy::getText()
{
	return m_DamageText;
}

bool Enemy::hit(int damage, int& enemiesLeft)
{
	m_Health -= damage;
	m_TotalDamage += damage;
	textTimer = 2.0f;
	m_DamageText.setString(std::to_string(m_TotalDamage));

	// Update the position of m_DamageText to align with the center of the Dummy
	FloatRect textRect = m_DamageText.getLocalBounds();
	m_DamageText.setPosition(
		getCenter().x - textRect.width / 2,
		getCenter().y - (textRect.height / 2) - 45
	);

	if (m_Health <= 0)
	{
		m_isAlive = false;
		enemiesLeft -= 1;

		return true;
	}

	return false;
}

bool Enemy::hitByAbility(int damage, int& enemiesLeft)
{
	if (m_lastHitByAbility < 0.0)
	{
		m_lastHitByAbility = 1.0;
		bool isDead = hit(damage, enemiesLeft);
		return isDead;
	}

	return false;
}

bool Enemy::hitBySlime(int damage, int& enemiesLeft)
{
	if (m_lastHitBySlime < 0.0)
	{
		m_lastHitBySlime = 1.0;
		bool isDead = hit(damage, enemiesLeft);
		return isDead;
	}

	return false;
}

void Enemy::cancelMovement() {
	m_Sprite.setPosition(prevPosition);
	m_Position = prevPosition;
}

bool Enemy::getIsAlive()
{
	return m_isAlive;
}

void Enemy::setIsOnWater(bool isSpiderOnWater)
{
	m_isOnWater = isSpiderOnWater;
}

bool Enemy::getFacingDirection()
{
	return m_facingLeft;
}