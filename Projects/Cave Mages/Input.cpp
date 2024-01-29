#include "Engine.h"
#include <iostream>

void Engine::input()
{
	Event event;

	if (m_inMainMenu)
	{
		// Player clicks play
		bool hoveringPlay = false;
		if (spriteCrosshair.getGlobalBounds().intersects(m_MainMenu.getPlayText().getGlobalBounds()))
		{
			hoveringPlay = true;
			if (!wasHoveringPlay) {
				m_SoundManager.playSelectTab();
				wasHoveringPlay = true;
			}
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				m_Playing = true;
				m_inMainMenu = false;
			}
		}
		if (!hoveringPlay) {
			wasHoveringPlay = false;
		}
		m_MainMenu.setHoveringPlay(hoveringPlay);

		// Player clicks exit
		bool hoveringExit = false;
		if (spriteCrosshair.getGlobalBounds().intersects(m_MainMenu.getExitText().getGlobalBounds()))
		{
			hoveringExit = true;
			if (!wasHoveringExit) {
				m_SoundManager.playSelectTab();
				wasHoveringExit = true;
			}
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				m_Window.close();
			}
		}
		if (!hoveringExit) {
			wasHoveringExit = false;
		}
		m_MainMenu.setHoveringExit(hoveringExit);
	}

	if (m_Playing)
	{
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (m_GameTimeTotal.asMilliseconds() - m_lastShot.asMilliseconds() > 1000 / m_fireMage.getFireRate())
			{
				// Pass the centre of the player 
				// and the centre of the cross-hair
				// to the shoot function
				// the number of bullets shot is equal to the multishot level
				Bullet* bullet = new FireBullet();
				if (m_fireMage.getFacingDirection()) {
					bullet->shoot(
						m_fireMage.getCenter().x - 30, m_fireMage.getCenter().y - 50,
						mouseWorldPosition.x, mouseWorldPosition.y, 1);
				}
				else {
					bullet->shoot(
						m_fireMage.getCenter().x + 30, m_fireMage.getCenter().y - 50,
						mouseWorldPosition.x, mouseWorldPosition.y, 1);
				}
				m_SoundManager.playFireBullet();
				m_lastShot = m_GameTimeTotal;
				bullets.push_back(bullet);

				if (m_Mimic.getIsAlive())
				{
					Bullet* mimicBullet = new MimicBullet();
					if (m_fireMage.getFacingDirection()) {
						mimicBullet->shoot(
							m_Mimic.getCenter().x - 30, m_Mimic.getCenter().y - 50,
							m_fireMage.getCenter().x, m_fireMage.getCenter().y, 1);
					}
					else {
						mimicBullet->shoot(
							m_Mimic.getCenter().x + 30, m_Mimic.getCenter().y - 50,
							m_fireMage.getCenter().x, m_fireMage.getCenter().y, 1);
					}
					mimicBullets.push_back(mimicBullet);
				}
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::E))
		{
			if ((m_GameTimeTotal.asSeconds() - m_lastAbility.asSeconds() > m_fireMage.getAbilityCooldown()) && !m_fireMage.getIsOnWater())
			{
				m_Ability.activate(m_fireMage.getAbilityActiveTime());
				// Play Sound
				m_SoundManager.playFireAbility();

				m_lastAbility = m_GameTimeTotal;
				m_fireMage.startAbilityCooldown();

				if (m_Mimic.getIsAlive())
				{
					m_MimicAbility.activate(m_fireMage.getAbilityActiveTime());
				}
			}
		}

		while (m_Window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed)
			{
				// Handle the player quitting
				if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					m_Window.close();
				}
			}
		}
		
		// Player wants to use deployable
		for (const auto& obstacle : obstacles) {
			if (auto* deployable = dynamic_cast<DeployableStation*>(obstacle)) {
				if (deployable->getIsPlayerInRange()) {
					if (Keyboard::isKeyPressed(Keyboard::F)) {
						m_currentDeployableStation = deployable;
						m_deployPosition = Vector2f(deployable->getPosition().left, deployable->getPosition().top);
						m_Playing = false;
						m_PickingDeployable = true;
					}
				}
			}
		}

		m_fireMage.handleInput();
	}
	
	// Player picking deployable
	if (m_PickingDeployable) {
		// Player clicks turret
		bool hoveringTurretIcon = false;
		if (spriteCrosshair.getGlobalBounds().intersects(m_DeployMenu.getTurretIcon().getGlobalBounds()))
		{
			hoveringTurretIcon = true;
			if (!wasHoveringTurretIcon) {
				m_SoundManager.playSelectTab();
				wasHoveringTurretIcon = true;
			}
			if (Mouse::isButtonPressed(Mouse::Left) && (m_fireMage.getXP() > turretCost))
			{
				m_currentDeployableStation->despawn();
				Deployable* turret = new FireTurret(m_deployPosition);
				deployables.push_back(turret);
				m_SoundManager.playCraftSound();

				// remove xp from player
				m_fireMage.spentXP(turretCost);

				m_deployableStationsToSpawn -= 1;

				m_Playing = true;
				m_PickingDeployable = false;
			}
		}
		if (!hoveringTurretIcon) {
			wasHoveringTurretIcon = false;
		}
		m_DeployMenu.setHoveringTurretIcon(hoveringTurretIcon);

		// Player clicks tree
		bool hoveringTreeIcon = false;
		if (spriteCrosshair.getGlobalBounds().intersects(m_DeployMenu.getTreeIcon().getGlobalBounds()))
		{
			hoveringTreeIcon = true;
			if (!wasHoveringTreeIcon) {
				m_SoundManager.playSelectTab();
				wasHoveringTreeIcon = true;
			}
			if (Mouse::isButtonPressed(Mouse::Left) && (m_fireMage.getXP() > treeCost))
			{
				m_currentDeployableStation->despawn();
				Deployable* tree = new LifeTree(m_deployPosition);
				deployables.push_back(tree);
				m_SoundManager.playCraftSound();

				//remove xp from player
				m_fireMage.spentXP(treeCost);

				m_deployableStationsToSpawn -= 1;

				m_Playing = true;
				m_PickingDeployable = false;
			}
		}
		if (!hoveringTreeIcon) {
			wasHoveringTreeIcon = false;
		}
		m_DeployMenu.setHoveringTreeIcon(hoveringTreeIcon);

		while (m_Window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed)
			{
				// Handle the player quitting
				if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					m_Playing = true;
					m_PickingDeployable = false;
				}
			}
		}
	}
}