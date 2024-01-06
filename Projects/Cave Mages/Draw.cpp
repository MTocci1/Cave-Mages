#include "Engine.h"
void Engine::draw()
{
	m_Window.clear();

	// Main View of player
	m_Window.setView(m_MainView);

	// Draw the background
	m_Window.draw(background, &textureBackground);

	if (m_inMainMenu) {
		// Display the Main  Menu
		// Set HUD View
		m_Window.setView(m_HudView);

		m_Window.draw(m_MainMenu.getPlayText());

		m_Window.draw(m_MainMenu.getExitText());

		m_Window.draw(m_MainMenu.getLogo());

		// Crosshair
		m_Window.draw(spriteCrosshair);
	}

	if (m_Playing) {
		// Main View of player
		m_Window.setView(m_MainView);

		// Obstacles
		// Water
		for (const auto& obstacle : obstacles) {
			if (auto* water = dynamic_cast<Water*>(obstacle)) {
				m_Window.draw(water->getSprite());
			}
		}
		// Health Station
		for (const auto& obstacle : obstacles) {
			if (auto* health = dynamic_cast<HealthStation*>(obstacle)) {
				m_Window.draw(health->getSprite());
			}
		}
		// Shield Station
		for (const auto& obstacle : obstacles) {
			if (auto* shield = dynamic_cast<ShieldStation*>(obstacle)) {
				m_Window.draw(shield->getSprite());
			}
		}
		// Deployable Station
		for (const auto& obstacle : obstacles) {
			if (auto* deployable = dynamic_cast<DeployableStation*>(obstacle)) {
				if (deployable->isSpawned()) {
					m_Window.draw(deployable->getSprite());
				}
			}
		}
		// Deployable Station Text
		for (const auto& obstacle : obstacles) {
			if (auto* deployable = dynamic_cast<DeployableStation*>(obstacle)) {
				if (deployable->isSpawned()) {
					m_Window.draw(deployable->getText());
				}
			}
		}

		// MimicAbility
		if (m_MimicAbility.isActive())
		{
			m_Window.draw(m_MimicAbility.getSprite());
		}
		// Player Ability
		if (m_Ability.isActive())
		{
			m_Window.draw(m_Ability.getSprite());
		}

		// Dummy
		m_Window.draw(m_dummy.getSprite());
		m_Window.draw(m_dummy.getText());

		// Bullets
		for (auto& bullet : bullets)
		{
			if (bullet->isInFlight())
			{
				m_Window.draw(bullet->getSprite());
			}
		}
		// Mummy Bullets
		for (auto& bullet : mummyBullets)
		{
			if (bullet->isInFlight())
			{
				m_Window.draw(bullet->getSprite());
			}
		}
		// Mimic Bullets
		for (auto& bullet : mimicBullets)
		{
			if (bullet->isInFlight())
			{
				m_Window.draw(bullet->getSprite());
			}
		}
		// Life Tree Bullets
		for (auto& bullet : lifeTreeBullets)
		{
			if (bullet->isInFlight())
			{
				m_Window.draw(bullet->getSprite());
			}
		}
		// Fire Turret Bullets
		for (auto& bullet : fireTurretBullets)
		{
			if (bullet->isInFlight())
			{
				m_Window.draw(bullet->getSprite());
			}
		}

		// The deployables
		for (auto& deployable : deployables) {
			if (deployable->getIsSpawned()) {
				m_Window.draw(deployable->getSprite());
			}
		}


		// Player
		m_Window.draw(m_fireMage.getSprite());

		// Snail
		m_Window.draw(m_Snail.getSprite());

		// Enemies not ghost or slime
		for (const auto& enemy : enemies) {
			if (!dynamic_cast<Ghost*>(enemy) && !dynamic_cast<Slime*>(enemy)) {
				if (enemy->getIsAlive()) {
					m_Window.draw(enemy->getSprite());
				}
			}
		}
		// Slimes
		for (const auto& enemy : enemies) {
			if (auto* slime = dynamic_cast<Slime*>(enemy)) {
				if (slime->getIsAlive()) {
					m_Window.draw(slime->getSprite());
				}
			}
		}
		// XP
		for (const auto& xp : xps) {
			if (xp->getIsSpawned()) {
				m_Window.draw(xp->getSprite());
			}
		}

		// Rocks
		for (const auto& obstacle : obstacles) {
			if (auto* rock = dynamic_cast<Wall*>(obstacle)) {
				m_Window.draw(rock->getSprite());
			}
		}
		// Ghosts
		for (const auto& enemy : enemies) {
			if (auto* ghost = dynamic_cast<Ghost*>(enemy)) {
				if (ghost->getIsAlive()) {
					m_Window.draw(ghost->getSprite());
				}
			}
		}

		// Damage Text
		for (const auto& enemy : enemies) {
			m_Window.draw(enemy->getText());
		}

		// Mimic
		if (m_Mimic.getIsAlive()) {
			m_Window.draw(m_Mimic.getSprite());
		}
		if (m_Mimic.getIsAlive()) {
			m_Window.draw(m_Mimic.getText());
		}
		
		// Crosshair
		m_Window.draw(spriteCrosshair);

		// Display the HUD
		// HUD View
		m_Window.setView(m_HudView);

		m_Window.draw(m_Hud.getHealth());

		m_Window.draw(m_Hud.getHealthBar());

		m_Window.draw(m_Hud.getShield());

		m_Window.draw(m_Hud.getShieldBar());

		if (m_Mimic.getIsAlive()) {
			m_Window.draw(m_Hud.getMimicText());
			m_Window.draw(m_Hud.getMimicHealthBar());
		}

		m_Window.draw(m_Hud.getWaveNumber());

		m_Window.draw(m_Hud.getEnemiesLeft());

		m_Window.draw(m_Hud.getXPText());

		m_Window.draw(m_Hud.getDashIcon());

		if (m_fireMage.getDashCooldown() != 3.0) {
			m_Window.draw(m_Hud.getDashCooldown());
		}

		m_Window.draw(m_Hud.getAbilityIcon());

		if (m_fireMage.getRealTimeAbilityCooldown() != 9.0) {
			m_Window.draw(m_Hud.getAbilityCooldown());
		}
	}

	// Show everything we have just drawn
	m_Window.display();
}