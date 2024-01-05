#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Hud
{
private:
	Font m_Font;
	Text m_HealthText;
	RectangleShape m_HealthBar;

	Text m_ShieldText;
	RectangleShape m_ShieldBar;

	Text m_WaveNumberText;
	Text m_EnemiesLeft;

	Text m_AbilityCooldown;
	Sprite m_AbilityIcon;

	Text m_DashCooldown;
	Sprite m_DashIcon;

	Text m_MimicText;
	RectangleShape m_MimicHealthBar;

	Text m_XPText;

public:
	Hud();

	Text getWaveNumber();

	Text getEnemiesLeft();

	Text getHealth();

	RectangleShape getHealthBar();

	Text getShield();

	RectangleShape getShieldBar();

	Text getAbilityCooldown();

	Sprite getAbilityIcon();

	Text getDashCooldown();

	Sprite getDashIcon();

	Text getMimicText();

	RectangleShape getMimicHealthBar();

	Text getXPText();

	void update(int health, int shield, int waveNumber, int enemiesLeft, float abilityCooldown, float dashCooldown, int mimicHealth, int XP);
};