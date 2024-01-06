#include "Engine.h"
#include <iostream>

void Engine::input()
{
	Event event;
	while (m_Window.pollEvent(event))
	{
		if (event.type == Event::KeyPressed)
		{
			// Handle the player quitting
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				m_Window.close();
			}
			// Handle the player starting the game
			if (Keyboard::isKeyPressed(Keyboard::Return))
			{
				m_Playing = true;
			}
		}
	}

	if (m_inMainMenu)
	{
		// Player clicks play
		bool hoveringPlay = false;
		if (spriteCrosshair.getGlobalBounds().intersects(m_MainMenu.getPlayText().getGlobalBounds()))
		{
			hoveringPlay = true;
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				m_Playing = true;
				m_inMainMenu = false;
			}
		}
		m_MainMenu.setHoveringPlay(hoveringPlay);

		// Player clicks exit
		bool hoveringExit = false;
		if (spriteCrosshair.getGlobalBounds().intersects(m_MainMenu.getExitText().getGlobalBounds()))
		{
			hoveringExit = true;
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				m_Window.close();
			}
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
				bullet->shoot(
					m_fireMage.getCenter().x + 30, m_fireMage.getCenter().y - 50,
					mouseWorldPosition.x, mouseWorldPosition.y, 1);
				m_lastShot = m_GameTimeTotal;
				bullets.push_back(bullet);

				if (m_Mimic.getIsAlive())
				{
					Bullet* mimicBullet = new MimicBullet();
					mimicBullet->shoot(
						m_Mimic.getCenter().x + 30, m_Mimic.getCenter().y - 50,
						m_fireMage.getCenter().x, m_fireMage.getCenter().y, 1);
					mimicBullets.push_back(mimicBullet);
				}
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::E))
		{
			if ((m_GameTimeTotal.asSeconds() - m_lastAbility.asSeconds() > m_fireMage.getAbilityCooldown()) && !m_fireMage.getIsOnWater())
			{
				m_Ability.activate(m_fireMage.getAbilityActiveTime());
				m_lastAbility = m_GameTimeTotal;
				m_fireMage.startAbilityCooldown();

				if (m_Mimic.getIsAlive())
				{
					m_MimicAbility.activate(m_fireMage.getAbilityActiveTime());
				}
			}
		}

		m_fireMage.handleInput();
	}
}