#include "HUD.h"
#include "TextureHolder.h"

Hud::Hud()
{
	Vector2u resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	// Load the font
	m_Font.loadFromFile("fonts/impact.ttf");

	// Health Text
	m_HealthText.setFont(m_Font);
	m_HealthText.setCharacterSize(25);
	m_HealthText.setFillColor(Color::White);
	m_HealthText.setPosition(50, 50);
	m_HealthText.setString("");

	m_HealthBar.setFillColor(Color::Green);
	m_HealthBar.setPosition(100, 50);

	// Shield Text
	m_ShieldText.setFont(m_Font);
	m_ShieldText.setCharacterSize(25);
	m_ShieldText.setFillColor(Color::White);
	m_ShieldText.setPosition(50, 100);
	m_ShieldText.setString("");

	m_ShieldBar.setFillColor(Color::Cyan);
	m_ShieldBar.setPosition(100, 100);

	// WaveNumber Text
	m_WaveNumberText.setFont(m_Font);
	m_WaveNumberText.setCharacterSize(25);
	m_WaveNumberText.setFillColor(Color::White);
	m_WaveNumberText.setPosition(resolution.x - 200, 50);
	m_WaveNumberText.setString("");

	// Enemies Left Text
	m_EnemiesLeft.setFont(m_Font);
	m_EnemiesLeft.setCharacterSize(25);
	m_EnemiesLeft.setFillColor(Color::White);
	m_EnemiesLeft.setPosition(resolution.x - 200, 100);
	m_EnemiesLeft.setString("");

	// Ability Icon
	// Associate a texture with the sprite
	m_AbilityIcon = Sprite(TextureHolder::GetTexture(
		"graphics/ability-icon.png"));
	m_AbilityIcon.setScale(.40, .40);
	m_AbilityIcon.setPosition(100, resolution.y - 200);

	// Ability Cooldown
	m_AbilityCooldown.setFont(m_Font);
	m_AbilityCooldown.setCharacterSize(50);
	m_AbilityCooldown.setFillColor(Color::Red);
	m_AbilityCooldown.setPosition(145, resolution.y - 150);
	m_AbilityCooldown.setString("");

	// Dash Icon
	// Associate a texture with the sprite
	m_DashIcon = Sprite(TextureHolder::GetTexture(
		"graphics/dash-icon.png"));
	m_DashIcon.setScale(.40, .40);
	m_DashIcon.setPosition(220, resolution.y - 200);

	// Dash Cooldown
	m_DashCooldown.setFont(m_Font);
	m_DashCooldown.setCharacterSize(50);
	m_DashCooldown.setFillColor(Color::Red);
	m_DashCooldown.setPosition(270, resolution.y - 150);
	m_DashCooldown.setString("");

	// Mimic Text
	m_MimicText.setFont(m_Font);
	m_MimicText.setCharacterSize(25);
	m_MimicText.setFillColor(Color::White);

	// Mimic Health Bar
	m_MimicHealthBar.setFillColor(Color::Red);

	// XP Text
	m_XPText.setFont(m_Font);
	m_XPText.setCharacterSize(25);
	m_XPText.setFillColor(Color::White);
	m_XPText.setPosition(resolution.x - 100, resolution.y / 2);
	m_XPText.setString("");

}

Text Hud::getWaveNumber()
{
	return m_WaveNumberText;
}

Text Hud::getEnemiesLeft()
{
	return m_EnemiesLeft;
}

Text Hud::getHealth()
{
	return m_HealthText;
}

RectangleShape Hud::getHealthBar()
{
	return m_HealthBar;
}

Text Hud::getShield()
{
	return m_ShieldText;
}

RectangleShape Hud::getShieldBar()
{
	return m_ShieldBar;
}

Text Hud::getAbilityCooldown()
{
	return m_AbilityCooldown;
}

Sprite Hud::getAbilityIcon()
{
	return m_AbilityIcon;
}

Text Hud::getDashCooldown()
{
	return m_DashCooldown;
}

Sprite Hud::getDashIcon()
{
	return m_DashIcon;
}

Text Hud::getMimicText()
{
	return m_MimicText;
}

Text Hud::getXPText()
{
	return m_XPText;
}

RectangleShape Hud::getMimicHealthBar()
{
	return m_MimicHealthBar;
}

void Hud::update(int health, int shield, int waveNumber, int enemiesLeft, float abilityCooldown, float dashCooldown, int mimicHealth, int XP)
{
	String healthText = std::to_string(health);
	m_HealthText.setString(healthText);

	m_HealthBar.setSize(Vector2f(health * 3, 25));

	String shieldText = std::to_string(shield);
	m_ShieldText.setString(shieldText);

	m_ShieldBar.setSize(Vector2f(shield * 3, 25));

	String waveNumberText = std::to_string(waveNumber);
	m_WaveNumberText.setString("Wave Number: " + waveNumberText);

	String enemiesLeftText = std::to_string(enemiesLeft);
	m_EnemiesLeft.setString("Enemies Left: " + enemiesLeftText);

	String abilityCooldownText = std::to_string(static_cast<int>(abilityCooldown));
	m_AbilityCooldown.setString(abilityCooldownText);

	String dashCooldownText = std::to_string(static_cast<int>(dashCooldown));
	m_DashCooldown.setString(dashCooldownText);

	m_MimicHealthBar.setSize(Vector2f(mimicHealth * 4, 25));

	// Center the Mimic Health Bar
	Vector2u resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	float textX = (resolution.x / 2) - (m_MimicText.getGlobalBounds().width / 2);
	float textY = 50;
	m_MimicText.setPosition(textX, textY);
	m_MimicText.setString("Mimic");

	float healthBarX = (resolution.x / 2) - (m_MimicHealthBar.getGlobalBounds().width / 2);
	float healthBarY = textY + m_MimicText.getLocalBounds().height + 10;
	m_MimicHealthBar.setPosition(healthBarX, healthBarY);

	// XP Text
	String XPText = std::to_string(XP);
	m_XPText.setString("XP: " + XPText);
}

