#include "PlayableCharacter.h"
#include <iostream>

void PlayableCharacter::spawn(IntRect arena, Vector2f resolution, int tileSize)
{
	// Place the player in the middle of the arena
	m_Position.x = arena.width / 2;
	m_Position.y = arena.height / 2;

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
}

void PlayableCharacter::update(float elapsedTime)
{
	m_SpeedOnWater = m_Speed / 2;
	m_dashSpeedOnWater = m_dashSpeed / 2;

	// Ensure health and shield stay within range
	if (m_Health > m_MaxHealth) {
		m_Health = m_MaxHealth;
	}
	if (m_Shield > m_MaxShield) {
		m_Shield = m_MaxShield;
	}

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

	// Move the player
	if (m_canMoveLeft) {
		if (m_LeftPressed)
		{
			if (m_isOnWater) {
				if (m_isDashing) {
					m_Position.x -= m_dashSpeedOnWater * elapsedTime * factor;
				}
				else {
					m_Position.x -= m_SpeedOnWater * elapsedTime * factor;
				}
			}
			else if (m_isDashing) {
				m_Position.x -= m_dashSpeed * elapsedTime * factor;
			}
			else {
				m_Position.x -= m_Speed * elapsedTime * factor;
			}
		}
	}
	if (m_canMoveRight) {
		if (m_RightPressed)
		{
			if (m_isOnWater) {
				if (m_isDashing) {
					m_Position.x += m_dashSpeedOnWater * elapsedTime * factor;
				}
				else {
					m_Position.x += m_SpeedOnWater * elapsedTime * factor;
				}
			}
			else if (m_isDashing) {
				m_Position.x += m_dashSpeed * elapsedTime * factor;
			}
			else {
				m_Position.x += m_Speed * elapsedTime * factor;
			}
		}
	}
	if (m_canMoveDown) {
		if (m_DownPressed)
		{
			if (m_isOnWater) {
				if (m_isDashing) {
					m_Position.y += m_dashSpeedOnWater * elapsedTime * factor;
				}
				else {
					m_Position.y += m_SpeedOnWater * elapsedTime * factor;
				}
			}
			else if (m_isDashing) {
				m_Position.y += m_dashSpeed * elapsedTime * factor;
			}
			else {
				m_Position.y += m_Speed * elapsedTime * factor;
			}
		}
	}
	if (m_canMoveUp) {
		if (m_UpPressed)
		{
			if (m_isOnWater) {
				if (m_isDashing) {
					m_Position.y -= m_dashSpeedOnWater * elapsedTime * factor;
				}
				else {
					m_Position.y -= m_SpeedOnWater * elapsedTime * factor;
				}
			}
			else if (m_isDashing) {
				m_Position.y -= m_dashSpeed * elapsedTime * factor;
			}
			else {
				m_Position.y -= m_Speed * elapsedTime * factor;
			}
		}
	}

	// Keep the player in the arena
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

	updateHitboxes();

	// Dash
	if (m_isDashing) 
	{
		m_dashDuration -= elapsedTime;
	}
	if (m_dashDuration < 0.0)
	{
		m_dashDuration = 0.2;
		m_isDashing = false;
	}

	if (!m_canDash)
	{
		m_dashCooldown -= elapsedTime;
	}
	if (m_dashCooldown < 0.0)
	{
		m_canDash = true;
		m_dashCooldown = 3.0;
	}

	// Ability
	if (!m_canUseAbility)
	{
		m_RealTimeAbilityCooldown -= elapsedTime;
	}
	if (m_RealTimeAbilityCooldown < 0.0)
	{
		m_canUseAbility = true;
		m_RealTimeAbilityCooldown = 9.0;
	}

	// Heal Station
	if (!m_canHeal)
	{
		m_healCooldown -= elapsedTime;
	}
	if (m_healCooldown < 0.0)
	{
		m_canHeal = true;
		m_healCooldown = 1.0;
	}

	// Shield Station
	if (!m_canShield)
	{
		m_shieldCooldown -= elapsedTime;
	}
	if (m_shieldCooldown < 0.0)
	{
		m_canShield = true;
		m_shieldCooldown = 1.0;
	}

	// Possessed
	if (m_isPossessed) {
		m_PossessedActiveTime -= elapsedTime;
	}

	if (m_PossessedActiveTime < 0.0) {
		m_isPossessed = false;
		m_PossessedActiveTime = 10.0;
	}

	// Poisoned
	if (m_isPoisoned) {
		m_PoisonActiveTime -= elapsedTime;
	}

	if (m_PoisonActiveTime < 0.0) {
		m_isPoisoned = false;
		m_PoisonActiveTime = 5.0;
	}
}

FloatRect PlayableCharacter::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Vector2f PlayableCharacter::getCenter()
{
	return Vector2f(
		m_Position.x + m_Sprite.getGlobalBounds().width / 2,
		m_Position.y + m_Sprite.getGlobalBounds().height / 2
	);
}

Sprite PlayableCharacter::getSprite()
{
	return m_Sprite;
}

float PlayableCharacter::getFireRate()
{
	return m_FireRate;
}

int PlayableCharacter::getDamage()
{
	return m_Damage;
}

bool PlayableCharacter::getFacingDirection()
{
	return m_facingLeft;
}

int PlayableCharacter::getHealth()
{
	return m_Health;
}

int PlayableCharacter::getShield()
{
	return m_Shield;
}

float PlayableCharacter::getAbilityCooldown()
{
	return m_abilityCooldown;
}
float PlayableCharacter::getAbilityActiveTime()
{
	return m_abilityActiveTime;
}
int PlayableCharacter::getAbilityDamage()
{
	return m_abilityDamage;
}
int PlayableCharacter::getSpeed()
{
	return m_Speed;
}
float PlayableCharacter::getRealTimeAbilityCooldown()
{
	return m_RealTimeAbilityCooldown;
}

float PlayableCharacter::getDashCooldown()
{
	return m_dashCooldown;
}

bool PlayableCharacter::getIsOnWater()
{
	return m_isOnWater;
}

bool PlayableCharacter::isSpawned()
{
	return m_Spawned;
}

void PlayableCharacter::setSpawn(bool spawn)
{
	m_Spawned = spawn;
}

void PlayableCharacter::dash()
{
	if (m_canDash)
	{
		m_isDashing = true;
		m_canDash = false;
	}
}

// Linear interpolation function
float PlayableCharacter::lerp(float position, float target, float factor)
{
	return position + factor * (target - position);
}


void PlayableCharacter::cancelMovement() {
	m_Sprite.setPosition(prevPosition);
	m_Position = prevPosition;
}

void PlayableCharacter::activatePossession() {
	m_isPossessed = true;
	m_PossessedActiveTime = 10.0f;
}

void PlayableCharacter::activatePoison() {
	m_isPoisoned = true;
	m_PoisonActiveTime = 5.0f;
}

void PlayableCharacter::setIsOnWater(bool isPlayerOnWater)
{
	m_isOnWater = isPlayerOnWater;
}

void PlayableCharacter::healthStationHeal()
{
	if (m_canHeal) {
		m_Health += 5;
		m_canHeal = false;
	}
}

void PlayableCharacter::shieldStationHeal()
{
	if (m_canShield) {
		m_Shield += 5;
		m_canShield = false;
	}
}

void PlayableCharacter::heal(int amount)
{
	m_Health += amount;
}

void PlayableCharacter::shield(int amount)
{
	m_Shield += amount;
}

void PlayableCharacter::startAbilityCooldown()
{
	m_canUseAbility = false;
}

int PlayableCharacter::getXP()
{
	return m_XP;
}

void PlayableCharacter::touchedXP(int value)
{
	m_XP += value;
}

void PlayableCharacter::spentXP(int value)
{
	m_XP -= value;
}

void PlayableCharacter::setFacingDirection(bool isAimingRight)
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

void PlayableCharacter::updateHitboxes()
{
	float headWidth = m_Sprite.getGlobalBounds().width * 0.5f;
	float headHeight = m_Sprite.getGlobalBounds().height * 0.2f;
	float feetWidth = m_Sprite.getGlobalBounds().width * 0.5f;
	float feetHeight = m_Sprite.getGlobalBounds().height * 0.2f;
	float sideWidth = m_Sprite.getGlobalBounds().width * 0.2f;
	float sideHeight = m_Sprite.getGlobalBounds().height * 0.6f;

	// Update hitbox positions based on the player's position
	m_HeadHitbox.left = m_Position.x + m_Sprite.getGlobalBounds().width / 2 - headWidth / 2;
	m_HeadHitbox.top = m_Position.y;
	m_HeadHitbox.width = headWidth;
	m_HeadHitbox.height = headHeight;

	m_FeetHitbox.left = m_Position.x + m_Sprite.getGlobalBounds().width / 2 - feetWidth / 2;
	m_FeetHitbox.top = m_Position.y + m_Sprite.getGlobalBounds().height - feetHeight;
	m_FeetHitbox.width = feetWidth;
	m_FeetHitbox.height = feetHeight;

	m_LeftHitbox.left = m_Position.x;
	m_LeftHitbox.top = m_Position.y + m_Sprite.getGlobalBounds().height / 2 - sideHeight / 2;
	m_LeftHitbox.width = sideWidth;
	m_LeftHitbox.height = sideHeight;

	m_RightHitbox.left = m_Position.x + m_Sprite.getGlobalBounds().width - sideWidth;
	m_RightHitbox.top = m_Position.y + m_Sprite.getGlobalBounds().height / 2 - sideHeight / 2;
	m_RightHitbox.width = sideWidth;
	m_RightHitbox.height = sideHeight;
}

FloatRect PlayableCharacter::getHeadHitBox()
{
	return m_HeadHitbox;
}

FloatRect PlayableCharacter::getFeetHitBox()
{
	return m_FeetHitbox;
}

FloatRect PlayableCharacter::getLeftHitBox()
{
	return m_LeftHitbox;
}

FloatRect PlayableCharacter::getRightHitBox()
{
	return m_RightHitbox;
}

void PlayableCharacter::setCanMoveUp(bool canMove)
{
	m_canMoveUp = canMove;
}

void PlayableCharacter::setCanMoveDown(bool canMove)
{
	m_canMoveDown = canMove;
}

void PlayableCharacter::setCanMoveLeft(bool canMove)
{
	m_canMoveLeft = canMove;
}

void PlayableCharacter::setCanMoveRight(bool canMove)
{
	m_canMoveRight = canMove;
}
