#include "fireMage.h"
#include "TextureHolder.h"

FireMage::FireMage()
{
	// Associate a texture with the sprite
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/fire-mage.png"));
	m_Sprite.setScale(.25, .25);

	// Player Stats
	// How fast is the character
	m_Speed = 700;
	m_SpeedOnWater = m_Speed / 2;
	m_dashSpeed = 1700;
	m_dashSpeedOnWater = m_dashSpeed / 2;

	m_Health = 100;
	m_MaxHealth = 100;
	m_Shield = 0;
	m_MaxShield = 100;

	m_FireRate = 1.0;
	m_Damage = 20;

	m_isDashing = false;
	m_dashDuration = 0.2f;
	m_canDash = true;
	m_dashCooldown = 3.0;

	m_abilityCooldown = 9.0f;
	m_abilityActiveTime = 3.0f;
	m_abilityDamage = 10;
	m_canUseAbility = false;
	m_RealTimeAbilityCooldown = 9.0f;

	m_isPossessed = false;
	m_PossessedActiveTime = 10.0f;

	m_isPoisoned = false;
	m_PoisonActiveTime = 5.0f;
	m_poisonDamage = 5;

	m_canHeal = true;
	m_healCooldown = 1.0f;
	m_healAmount = 5;

	m_canShield = true;
	m_shieldCooldown = 1.0f;
	m_shieldAmount = 5;
}

void FireMage::handleInput()
{
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		if (!m_isPossessed) {
			m_UpPressed = true;
		}
		// Inverse Controls if the player is possessed
		else {
			m_DownPressed = true;
		}
	}
	else
	{
		if (!m_isPossessed) {
			m_UpPressed = false;
		}
		else {
			m_DownPressed = false;
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		if (!m_isPossessed) {
			m_DownPressed = true;
		}
		else {
			m_UpPressed = true;
		}
	}
	else
	{
		if (!m_isPossessed) {
			m_DownPressed = false;
		}
		else {
			m_UpPressed = false;
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		if (!m_isPossessed) {
			m_LeftPressed = true;
		}
		else {
			m_RightPressed = true;
		}
	}
	else
	{
		if (!m_isPossessed) {
			m_LeftPressed = false;
		}
		else {
			m_RightPressed = false;
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		if (!m_isPossessed) {
			m_RightPressed = true;
		}
		else {
			m_LeftPressed = true;
		}
	}
	else
	{
		if (!m_isPossessed) {
			m_RightPressed = false;
		}
		else {
			m_LeftPressed = false;
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		dash();
	}

	// Change Spirte is the player is poisoned
	if (m_isPoisoned) {
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/fire-mage-poisoned.png"));
		m_Sprite.setPosition(m_Position);
	}
	else {
		m_Sprite = Sprite(TextureHolder::GetTexture(
			"graphics/fire-mage.png"));
		m_Sprite.setPosition(m_Position);
	}
}