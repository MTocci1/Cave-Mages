#include "Engine.h"
#include <iostream>

using namespace sf;

void Engine::update(float dtAsSeconds)
{
	if (m_Playing)
	{
		if (m_NewWaveRequired)
		{
			// Delete all enemies, free memory
			for (const auto& enemy : enemies) {
				delete enemy;
			}
			// Clear the enemies array
			enemies.clear();

			// Delete all obstacles, free memory
			for (const auto& obstacle : obstacles) {
				delete obstacle;
			}
			// Clear the enemies array
			obstacles.clear();

			// Load a Wave
			loadWave();
		}

		// Wave Completed
		if (m_EnemiesLeft == 0)
		{
			m_WaveNumber += 1;
			m_NewWaveRequired = true;
		}

		// Where is the mouse pointer
		mouseScreenPosition = Mouse::getPosition();

		// Convert mouse position to world coordinates of mainView
		mouseWorldPosition = m_Window.mapPixelToCoords(
			Mouse::getPosition(), m_MainView);

		// Hide the mouse curser
		m_Window.setMouseCursorVisible(false);

		// Set the crosshair to the mouse world location
		spriteCrosshair.setPosition(mouseWorldPosition);

		// Update fireMage
		m_fireMage.update(dtAsSeconds);

		// Update dummy
		m_dummy.update(dtAsSeconds);

		m_Mimic.update(dtAsSeconds, m_fireMage.getFacingDirection(), m_fireMage.getCenter());

		// Update all enemies except slime
		for (const auto& enemy : enemies) {
			if (!dynamic_cast<Slime*>(enemy)) {
				enemy->update(dtAsSeconds, m_fireMage.getFacingDirection(), m_fireMage.getCenter());
			}
		}
		// Update slime
		for (auto& enemy : enemies) {
			if (auto* slimeEnemy = dynamic_cast<Slime*>(enemy)) {
				Vector2f closestTargetPosition = findClosestSlimeTarget(*slimeEnemy, enemies, m_fireMage);
				slimeEnemy->update(dtAsSeconds, m_fireMage.getFacingDirection(), closestTargetPosition);
			}
		}

		// Update All XPs
		for (auto& xp : xps) {
			xp->update(dtAsSeconds, m_fireMage.getCenter());
		}

		// Update all deployables
		for (auto& deployable : deployables)
		{
			deployable->update(dtAsSeconds, m_fireMage.getCenter());
		}

		// Update the snail
		m_Snail.update(dtAsSeconds, m_fireMage.getFacingDirection(), m_fireMage.getCenter());

		// Update Ability
		m_Ability.update(dtAsSeconds, m_fireMage.getCenter().x, m_fireMage.getCenter().y);

		// Update Mimic Ability
		m_MimicAbility.update(dtAsSeconds, m_Mimic.getCenter().x, m_Mimic.getCenter().y);

		// Update HUD
		m_Hud.update(m_fireMage.getHealth(), m_fireMage.getShield(), m_WaveNumber, m_EnemiesLeft, m_fireMage.getRealTimeAbilityCooldown(),
			m_fireMage.getDashCooldown(), m_Mimic.getHealth(), m_fireMage.getXP());

		// Detect Collisions
		// Player collide with dummy
		if (m_fireMage.getPosition().intersects(m_dummy.getPosition()))
		{
			m_fireMage.cancelMovement();
		}
		// Player collide with Rock
		for (const auto& obstacle : obstacles) {
			if (auto* rock = dynamic_cast<Wall*>(obstacle)) {
				if (m_fireMage.getPosition().intersects(rock->getPosition()))
				{
					m_fireMage.cancelMovement();
				}
			}
		}
		// Player collide with Water
		// Assume initially the player is not on water
		bool playerOnWater = false;
		for (const auto& obstacle : obstacles) {
			if (auto* water = dynamic_cast<Water*>(obstacle)) {
				if (m_fireMage.getPosition().intersects(water->getPosition())) {
					playerOnWater = true;
					// Exit the loop once a collision is detected
					break;
				}
			}
		}
		// Set the player's water state based on the result of the loop
		m_fireMage.setIsOnWater(playerOnWater);

		// Player collide with DeployableStation
		for (const auto& obstacle : obstacles) {
			if (auto* deployable = dynamic_cast<DeployableStation*>(obstacle)) {
				if (m_fireMage.getPosition().intersects(deployable->getPosition())) {
					m_fireMage.cancelMovement();
					// Exit the loop once a collision is detected
					break;
				}
			}
		}
		// Player collide with Deployable
		for (const auto& deployable : deployables) {
			if (m_fireMage.getPosition().intersects(deployable->getPosition())) {
				m_fireMage.cancelMovement();
				// Exit the loop once a collision is detected
				break;
			}
		}
		// Is player in range of Deployable Station?
		// Player collide with DeployableStation
		for (const auto& obstacle : obstacles) {
			if (auto* deployable = dynamic_cast<DeployableStation*>(obstacle)) {
				deployable->isPlayerInRange(m_fireMage.getCenter());
			}
		}

		// Player collide with Health Station
		for (const auto& obstacle : obstacles) {
			if (auto* health = dynamic_cast<HealthStation*>(obstacle)) {
				if (m_fireMage.getPosition().intersects(health->getPosition()))
				{
					m_fireMage.healthStationHeal();
				}
			}
		}
		// Player collide with Shield Station
		for (const auto& obstacle : obstacles) {
			if (auto* shield = dynamic_cast<ShieldStation*>(obstacle)) {
				if (m_fireMage.getPosition().intersects(shield->getPosition()))
				{
					m_fireMage.shieldStationHeal();
				}
			}
		}


		// Has ability hit anything?
		// Hit Dummy?
		if (m_Ability.getPosition().intersects(m_dummy.getPosition()))
		{
			if (m_Ability.isActive())
			{
				m_dummy.hitByAbility(m_fireMage.getAbilityDamage());
			}
		}
		// Hit an enemy?
		for (const auto& enemy : enemies) {
			if (enemy->getIsAlive()) {
				if (m_Ability.getPosition().intersects(enemy->getPosition()))
				{
					if (m_Ability.isActive())
					{
						enemy->hitByAbility(m_fireMage.getAbilityDamage(), m_EnemiesLeft);
					}
				}
			}
		}
		// Hit Mimic
		if (m_Ability.getPosition().intersects(m_Mimic.getPosition()))
		{
			if (m_Ability.isActive())
			{
				m_Mimic.hitByAbility(m_fireMage.getAbilityDamage(), m_EnemiesLeft);
			}
		}

		// Has an enemy touched a player?
		// Has a ghost touched the player?
		for (const auto& enemy : enemies) {
			if (enemy->getIsAlive()) {
				if (auto* ghost = dynamic_cast<Ghost*>(enemy)) {
					if (ghost->getPosition().intersects(m_fireMage.getPosition()))
					{
						// Invert the player controls
						m_fireMage.activatePossession();
						ghost->hitPlayer(m_EnemiesLeft);
					}
				}
			}
		}
		// Has a Scorpion touched the player?
		for (const auto& enemy : enemies) {
			if (enemy->getIsAlive()) {
				if (auto* scorpion = dynamic_cast<Scorpion*>(enemy)) {
					if (scorpion->getPosition().intersects(m_fireMage.getPosition()))
					{
						// Invert the player controls
						m_fireMage.activatePoison();
						scorpion->activateFlee();
					}
				}
			}
		}
		// Is Mummy Close enough to the player
		// If so, shoot
		for (const auto& enemy : enemies) {
			if (enemy->getIsAlive()) {
				if (auto* mummy = dynamic_cast<Mummy*>(enemy)) {
					if (mummy->getIsPlayerInRange()) {
						if (m_GameTimeTotal.asMilliseconds() - mummy->getLastShot().asMilliseconds() > 1000 / mummy->getFireRate()) {
							Bullet* bullet = new MummyBullet();
							bullet->shoot(
								mummy->getCenter().x, mummy->getCenter().y,
								m_fireMage.getCenter().x, m_fireMage.getCenter().y, 1);
							mummy->setLastShot(m_GameTimeTotal);
							mummyBullets.push_back(bullet);
						}
					}
				}
			}
		}
		// Has Mummy Bullet hit the player?
		for (auto& bullet : mummyBullets) {
			if (bullet->getPosition().intersects(m_fireMage.getPosition())) {
				if (bullet->isInFlight()) {
					bullet->stop();
				}
			}
		}
		// Has Mimic Bullet hit the player?
		for (auto& bullet : mimicBullets) {
			if (bullet->getPosition().intersects(m_fireMage.getPosition())) {
				if (bullet->isInFlight()) {
					bullet->stop();
				}
			}
		}




		// Has a enemy besides ghost and slime touched a rock?
		for (const auto& enemy : enemies) {
			if (enemy->getIsAlive() && !dynamic_cast<Ghost*>(enemy) && !dynamic_cast<Slime*>(enemy)) {
				for (const auto& obstacle : obstacles)
				{
					if (auto* rock = dynamic_cast<Wall*>(obstacle))
						if (enemy->getPosition().intersects(rock->getPosition()))
						{
							enemy->cancelMovement();
						}
				}
			}
		}
		// Has a enemy besides ghost and slime touched a deployable?
		for (const auto& enemy : enemies) {
			if (enemy->getIsAlive() && !dynamic_cast<Ghost*>(enemy) && !dynamic_cast<Slime*>(enemy)) {
				for (const auto& deployable : deployables)
				{
					if (enemy->getPosition().intersects(deployable->getPosition()))
					{
						enemy->cancelMovement();
					}
				}
			}
		}
		// Has a enemy besides ghost and slime touched the dummy?
		for (const auto& enemy : enemies) {
			if (enemy->getIsAlive() && !dynamic_cast<Ghost*>(enemy) && !dynamic_cast<Slime*>(enemy)) {
				if (enemy->getPosition().intersects(m_dummy.getPosition()))
				{
					enemy->cancelMovement();
				}
			}
		}
		// Has snail touched a rock
		for (const auto& obstacle : obstacles)
		{
			if (auto* rock = dynamic_cast<Wall*>(obstacle)) {
				if (m_Snail.getPosition().intersects(rock->getPosition()))
				{
					m_Snail.cancelMovement();
				}
			}
		}
		// Has snail touched a deployable
		for (const auto& deployable : deployables)
		{
			if (m_Snail.getPosition().intersects(deployable->getPosition()))
			{
				m_Snail.cancelMovement();
			}
		}
		// Has snail touched dummy
		if (m_Snail.getPosition().intersects(m_dummy.getPosition()))
		{
			m_Snail.cancelMovement();
		}
		// Has mimic touched a rock
		for (const auto& obstacle : obstacles)
		{
			if (auto* rock = dynamic_cast<Wall*>(obstacle)) {
				if (m_Mimic.getPosition().intersects(rock->getPosition()))
				{
					m_Mimic.cancelMovement();
				}
			}
		}
		// Has mimic touched a deployable
		for (const auto& deployable : deployables)
		{
			if (m_Mimic.getPosition().intersects(deployable->getPosition()))
			{
				m_Mimic.cancelMovement();
			}
		}
		// Has mimic touched dummy
		if (m_Mimic.getPosition().intersects(m_dummy.getPosition()))
		{
			m_Mimic.cancelMovement();
		}

		// Check for slime-enemy and slime-slime intersections
		bool slimesIntersected = false;
		for (Enemy* enemy1 : enemies) {
			if (enemy1->getIsAlive()) {
				if (auto* slime1 = dynamic_cast<Slime*>(enemy1)) {
					for (Enemy* enemy2 : enemies) {
						if (enemy2->getIsAlive() && !dynamic_cast<Ghost*>(enemy2)) {
							if (enemy1 != enemy2 && enemy1->getPosition().intersects(enemy2->getPosition())) {
								// Slime-slime
								if (auto* slime2 = dynamic_cast<Slime*>(enemy2)) {
									// Ensure hitBySlime is called only once when slimes intersect
									if (!slimesIntersected) {
										slime1->touchedOtherSlime(slime2->getLevel(), slime2->getHealth());
										slime2->hitBySlime(1000, m_EnemiesLeft);
										slimesIntersected = true;
									}
								}
								// Slime-enemy
								else {
									bool killedEnemy = enemy2->hitBySlime(slime1->getDamage(), m_EnemiesLeft);
									if (killedEnemy) {
										slime1->eatenEnemy();
									}
								}
							}
						}
					}
				}
			}
		}




		// Spider collide with Water
		// Assume initially the spider is not on water
		bool spiderOnWater = false;
		for (const auto& enemy : enemies) {
			if (auto* spider = dynamic_cast<Spider*>(enemy)) {
				for (const auto& obstacle : obstacles) {
					if (auto* water = dynamic_cast<Water*>(obstacle)) {
						if (spider->getPosition().intersects(water->getPosition())) {
							// Set spider if the enemy is a spider
							spiderOnWater = true;
							spider->setIsOnWater(spiderOnWater);
							// Exit the loop once a collision is detected
							break;
						}
						else
						{
							spider->setIsOnWater(spiderOnWater);
						}
					}
				}
			}
		}
		// Scorpion collide with Water
		// Assume initially the Scorpion is not on water
		bool scorpionOnWater = false;
		for (const auto& enemy : enemies) {
			if (auto* scorpion = dynamic_cast<Scorpion*>(enemy)) {
				for (const auto& obstacle : obstacles) {
					if (auto* water = dynamic_cast<Water*>(obstacle)) {
						if (scorpion->getPosition().intersects(water->getPosition())) {
							// Set spider if the enemy is a spider
							scorpionOnWater = true;
							scorpion->setIsOnWater(scorpionOnWater);
							// Exit the loop once a collision is detected
							break;
						}
						else
						{
							scorpion->setIsOnWater(scorpionOnWater);
						}
					}
				}
			}
		}
		// Mummy collide with Water
		// Assume initially the Mummy is not on water
		bool mummyOnWater = false;
		for (const auto& enemy : enemies) {
			if (auto* mummy = dynamic_cast<Mummy*>(enemy)) {
				for (const auto& obstacle : obstacles) {
					if (auto* water = dynamic_cast<Water*>(obstacle)) {
						if (mummy->getIsAlive()) {
							if (mummy->getPosition().intersects(water->getPosition())) {
								// Set spider if the enemy is a spider
								mummyOnWater = true;
								mummy->IsOnWater(mummyOnWater, m_EnemiesLeft);
								// Exit the loop once a collision is detected
								break;
							}
							else
							{
								mummy->IsOnWater(mummyOnWater, m_EnemiesLeft);
							}
						}
					}
				}
			}
		}
		bool mimicOnWater = false;
		if (m_Mimic.getIsAlive()) {
			for (const auto& obstacle : obstacles) {
				if (auto* water = dynamic_cast<Water*>(obstacle)) {
					if (m_Mimic.getPosition().intersects(water->getPosition())) {
						// Set spider if the enemy is a spider
						mimicOnWater = true;
						m_Mimic.setIsOnWater(mimicOnWater);
						// Exit the loop once a collision is detected
						break;
					}
					else
					{
						m_Mimic.setIsOnWater(mimicOnWater);
					}
				}
			}
		}
		//Slime Collisions
		// Slime collide with Water
		// Assume initially the slime is not on water
		bool slimeOnWater = false;
		for (const auto& enemy : enemies) {
			if (auto* slime = dynamic_cast<Slime*>(enemy)) {
				for (const auto& obstacle : obstacles) {
					if (auto* water = dynamic_cast<Water*>(obstacle)) {
						if (slime->getPosition().intersects(water->getPosition())) {
							// Set spider if the enemy is a spider
							slimeOnWater = true;
							slime->setIsOnWater(slimeOnWater);
							// Exit the loop once a collision is detected
							break;
						}
						else
						{
							slime->setIsOnWater(slimeOnWater);
						}
					}
				}
			}
		}
		// Slime collide with Rock or dummy
		// Assume initially the slime is not on rock
		bool slimeOnRock = false;
		for (const auto& enemy : enemies) {
			if (auto* slime = dynamic_cast<Slime*>(enemy)) {
				for (const auto& obstacle : obstacles) {
					if (auto* rock = dynamic_cast<Wall*>(obstacle)) {
						if (slime->getPosition().intersects(rock->getPosition()) || slime->getPosition().intersects(m_dummy.getPosition())) {
							// Set spider if the enemy is a spider
							slimeOnRock = true;
							slime->setIsOnRock(slimeOnRock);
							// Exit the loop once a collision is detected
							break;
						}
						else
						{
							slime->setIsOnRock(slimeOnRock);
						}
					}
				}
			}
		}

		//XP Collisions
		// Has XP Collided with Obstacle
		for (auto& xp : xps) {
			if (xp->getIsSpawned()) {
				for (auto& obstacle : obstacles) {
					if (auto* rock = dynamic_cast<Wall*>(obstacle)) {
						if (xp->getPosition().intersects(rock->getPosition())) {
							xp->cancelMovement();
						}
					}
				}
			}
		}
		// Has XP collided with dummy?
		for (auto& xp : xps) {
			if (xp->getIsSpawned()) {
				if (xp->getPosition().intersects(m_dummy.getPosition())){
					xp->cancelMovement();
				}
			}
		}
		// Has XP collided with player?
		for (auto& xp : xps) {
			if (xp->getIsSpawned()) {
				if (xp->getPosition().intersects(m_fireMage.getPosition())) {
					m_fireMage.touchedXP(xp->getValue());
					xp->touchedByPlayer();
				}
			}
		}

		// Can a tree of life shoot
		for (auto& deployable : deployables) {
			if (deployable->getIsSpawned()) {
				if (auto* tree = dynamic_cast<LifeTree*>(deployable)) {
					if (tree->getIsPlayerInRange()) {
						if (m_GameTimeTotal.asMilliseconds() - tree->getLastShot().asMilliseconds() > 1500 / tree->getFireRate()){
							Bullet* bullet = new LifeTreeBullet(tree->getHealAmount());
							bullet->shoot(
								tree->getCenter().x, tree->getCenter().y,
								m_fireMage.getCenter().x, m_fireMage.getCenter().y, 1);
							tree->setLastShot(m_GameTimeTotal);
							lifeTreeBullets.push_back(bullet);
						}
					}
				}
			}
		}

		// Can a Fire Turret shoot
		for (auto& deployable : deployables) {
			if (deployable->getIsSpawned()) {
				if (auto* turret = dynamic_cast<FireTurret*>(deployable)) {
					if (isEnemyCloseToTurret(*turret, enemies)) {
						if (m_GameTimeTotal.asMilliseconds() - turret->getLastShot().asMilliseconds() > 1500 / turret->getFireRate()) {
							Vector2f closestTargetPosition = findClosestEnemyToTurret(*turret, enemies);
							Bullet* bullet = new FireTurretBullet(turret->getDamage());
							bullet->shoot(
								turret->getCenter().x, turret->getCenter().y,
								closestTargetPosition.x, closestTargetPosition.y, 1);
							turret->setLastShot(m_GameTimeTotal);
							fireTurretBullets.push_back(bullet);
						}
					}
				}
			}
		}
		// Delayed Fire Turret Shot
		for (auto& deployable : deployables) {
			if (deployable->getIsSpawned()) {
				if (auto* turret = dynamic_cast<FireTurret*>(deployable)) {
					if (isEnemyCloseToTurret(*turret, enemies)) {
						if (m_GameTimeTotal.asMilliseconds() - turret->getLastDelayedShot().asMilliseconds() > 1700 / turret->getFireRate()) {
							Bullet* bullet = new FireTurretBullet(turret->getDamage());
							Vector2f closestTargetPosition = findClosestEnemyToTurret(*turret, enemies);
							bullet->shoot(
								turret->getCenter().x, turret->getCenter().y,
								closestTargetPosition.x, closestTargetPosition.y, 1);
							turret->setLastDelayedShot(m_GameTimeTotal);
							fireTurretBullets.push_back(bullet);
						}
					}
				}
			}
		}



		// Update any bullets that are in-flight
		for (auto& bullet : bullets)
		{
			if (bullet->isInFlight())
			{
				bullet->update(dtAsSeconds);
			}
		}
		for (auto& bullet : mummyBullets)
		{
			if (auto* mummyBullet = dynamic_cast<MummyBullet*>(bullet)) {
				if (bullet->isInFlight())
				{
					mummyBullet->update(dtAsSeconds);
					mummyBullet->rotate(dtAsSeconds);
				}
			}
		}
		for (auto& bullet : mimicBullets)
		{
			if (bullet->isInFlight())
			{
				bullet->update(dtAsSeconds);
			}
		}
		for (auto& treeBullet : lifeTreeBullets)
		{
			if (auto* bullet = dynamic_cast<LifeTreeBullet*>(treeBullet)) {
				if (bullet->isInFlight())
				{
					bullet->followPlayer(m_fireMage.getCenter(), dtAsSeconds);
				}
			}
		}
		for (auto& fireTurretBullet : fireTurretBullets)
		{
			if (auto* bullet = dynamic_cast<FireTurretBullet*>(fireTurretBullet)) {
				if (bullet->isInFlight())
				{
					bullet->update(dtAsSeconds);
				}
			}
		}

		// Has a bullet hit the dummy or enemy 
		for (auto& bullet : bullets)
		{
			if (bullet->getPosition().intersects(m_dummy.getPosition()))
			{
				if (bullet->isInFlight())
				{
					bullet->stop();
					m_dummy.hit(m_fireMage.getDamage());
				}
			}

			if (bullet->getPosition().intersects(m_Mimic.getPosition()))
			{
				if (bullet->isInFlight())
				{
					bullet->stop();
					bool killed = m_Mimic.hit(m_fireMage.getDamage(), m_EnemiesLeft);
					if (killed) {
						m_fireMage.touchedXP(500);
					}
				}
			}

			if (bullet->getPosition().intersects(m_Snail.getPosition()))
			{
				if (bullet->isInFlight())
				{
					bullet->stop();
				}
			}


			for (const auto& enemy : enemies) {
				if (enemy->getIsAlive()) {
					if (bullet->getPosition().intersects(enemy->getPosition()))
					{
						if (bullet->isInFlight())
						{
							bullet->stop();
							bool killed = enemy->hit(m_fireMage.getDamage(), m_EnemiesLeft);
							// Spawn XP if enemy is killed
							if (killed) {
								// if Spider
								if (auto* spider = dynamic_cast<Spider*>(enemy)) { 
									XP* bronze1 = new Bronze(spider->getCenter().x, spider->getCenter().y, arena, resolution, TILE_SIZE);
									xps.push_back(bronze1);
									XP* bronze2 = new Bronze(spider->getCenter().x + 20, spider->getCenter().y, arena, resolution, TILE_SIZE);
									xps.push_back(bronze2);
								}
								// Slime
								else if (auto* slime = dynamic_cast<Slime*>(enemy)) {
									XP* bronze1 = new Bronze(slime->getCenter().x, slime->getCenter().y + 20, arena, resolution, TILE_SIZE);
									xps.push_back(bronze1);
									XP* silver1 = new Silver(slime->getCenter().x, slime->getCenter().y, arena, resolution, TILE_SIZE);
									xps.push_back(silver1);
									XP* silver2 = new Silver(slime->getCenter().x + 20, slime->getCenter().y, arena, resolution, TILE_SIZE);
									xps.push_back(silver2);
								}
								// Slime
								else if (auto* scorpion = dynamic_cast<Scorpion*>(enemy)) {
									XP* bronze1 = new Bronze(scorpion->getCenter().x, scorpion->getCenter().y + 20, arena, resolution, TILE_SIZE);
									xps.push_back(bronze1);
									XP* silver1 = new Silver(scorpion->getCenter().x, scorpion->getCenter().y + 20, arena, resolution, TILE_SIZE);
									xps.push_back(silver1);
									XP* silver2 = new Silver(scorpion->getCenter().x + 20, scorpion->getCenter().y, arena, resolution, TILE_SIZE);
									xps.push_back(silver2);

								}
								// Ghost
								else if (auto* ghost = dynamic_cast<Ghost*>(enemy)) {
									XP* bronze1 = new Bronze(ghost->getCenter().x, ghost->getCenter().y, arena, resolution, TILE_SIZE);
									xps.push_back(bronze1);
									XP* bronze2 = new Bronze(ghost->getCenter().x + 20, ghost->getCenter().y, arena, resolution, TILE_SIZE);
									xps.push_back(bronze2);
								}
								// Mummy
								else if (auto* mummy = dynamic_cast<Mummy*>(enemy)) {
									XP* gold = new Gold(mummy->getCenter().x, mummy->getCenter().y + 20, arena, resolution, TILE_SIZE);
									xps.push_back(gold);
									XP* bronze1 = new Bronze(mummy->getCenter().x + 20, mummy->getCenter().y + 20, arena, resolution, TILE_SIZE);
									xps.push_back(bronze1);
									XP* silver1 = new Silver(mummy->getCenter().x + 20, mummy->getCenter().y + 50, arena, resolution, TILE_SIZE);
									xps.push_back(silver1);
									XP* silver2 = new Silver(mummy->getCenter().x + 20, mummy->getCenter().y, arena, resolution, TILE_SIZE);
									xps.push_back(silver2);
								}
							}
						}
					}
				}
			}

			for (const auto& obstacle : obstacles) {
				if (auto* rock = dynamic_cast<Wall*>(obstacle)) {
					if (bullet->getPosition().intersects(rock->getPosition()))
					{
						if (bullet->isInFlight())
						{
							bullet->stop();
						}
					}
				}
			}
		}

		// Has Mummy Bullet hit an obstacle?
		for (auto& bullet : mummyBullets)
		{
			for (const auto& obstacle : obstacles) {
				if (auto* rock = dynamic_cast<Wall*>(obstacle)) {
					if (bullet->getPosition().intersects(rock->getPosition()))
					{
						if (bullet->isInFlight())
						{
							bullet->stop();
						}
					}
				}
			}

			// Hit Dummy?
			if (bullet->getPosition().intersects(m_dummy.getPosition()))
			{
				if (bullet->isInFlight())
				{
					bullet->stop();
				}
			}

		}
		// Has mimic Bullet hit an obstacle?
		for (auto& bullet : mimicBullets)
		{
			for (const auto& obstacle : obstacles) {
				if (auto* rock = dynamic_cast<Wall*>(obstacle)) {
					if (bullet->getPosition().intersects(rock->getPosition()))
					{
						if (bullet->isInFlight())
						{
							bullet->stop();
						}
					}
				}
			}

			if (bullet->getPosition().intersects(m_dummy.getPosition()))
			{
				if (bullet->isInFlight())
				{
					bullet->stop();
				}
			}
		}

		// Has Life Tree Bullet hit an obstacle?
		for (auto& treeBullet : lifeTreeBullets)
		{
			if (auto* bullet = dynamic_cast<LifeTreeBullet*>(treeBullet)){
				for (const auto& obstacle : obstacles) {
					if (auto* rock = dynamic_cast<Wall*>(obstacle)) {
						if (bullet->getPosition().intersects(rock->getPosition()))
						{
							if (bullet->isInFlight())
							{
								bullet->stop();
							}
						}
					}
				}

				if (bullet->getPosition().intersects(m_dummy.getPosition()))
				{
					if (bullet->isInFlight())
					{
						bullet->stop();
					}
				}

				if (bullet->getPosition().intersects(m_fireMage.getPosition()))
				{
					if (bullet->isInFlight())
					{
						m_fireMage.shield(bullet->getHealAmount());
						bullet->stop();
					}
				}
			}
		}

		// Has a Fire Turret Bullet hit anything?
		for (auto& fireTurretBullet : fireTurretBullets)
		{
			if (auto* bullet = dynamic_cast<FireTurretBullet*>(fireTurretBullet)) {
				if (bullet->getPosition().intersects(m_dummy.getPosition()))
				{
					if (bullet->isInFlight())
					{
						bullet->stop();
						m_dummy.hit(bullet->getDamage());
					}
				}

				if (bullet->getPosition().intersects(m_Mimic.getPosition()))
				{
					if (bullet->isInFlight())
					{
						bullet->stop();
						bool killed = m_Mimic.hit(bullet->getDamage(), m_EnemiesLeft);
						if (killed) {
							m_fireMage.touchedXP(500);
						}
					}
				}

				if (bullet->getPosition().intersects(m_Snail.getPosition()))
				{
					if (bullet->isInFlight())
					{
						bullet->stop();
					}
				}


				for (const auto& enemy : enemies) {
					if (enemy->getIsAlive()) {
						if (bullet->getPosition().intersects(enemy->getPosition()))
						{
							if (bullet->isInFlight())
							{
								bullet->stop();
								bool killed = enemy->hit(bullet->getDamage(), m_EnemiesLeft);
								// Spawn XP if enemy is killed
								if (killed) {
									// if Spider
									if (auto* spider = dynamic_cast<Spider*>(enemy)) {
										XP* bronze1 = new Bronze(spider->getCenter().x, spider->getCenter().y, arena, resolution, TILE_SIZE);
										xps.push_back(bronze1);
										XP* bronze2 = new Bronze(spider->getCenter().x + 20, spider->getCenter().y, arena, resolution, TILE_SIZE);
										xps.push_back(bronze2);
									}
									// Slime
									else if (auto* slime = dynamic_cast<Slime*>(enemy)) {
										XP* bronze1 = new Bronze(slime->getCenter().x, slime->getCenter().y + 20, arena, resolution, TILE_SIZE);
										xps.push_back(bronze1);
										XP* silver1 = new Silver(slime->getCenter().x, slime->getCenter().y, arena, resolution, TILE_SIZE);
										xps.push_back(silver1);
										XP* silver2 = new Silver(slime->getCenter().x + 20, slime->getCenter().y, arena, resolution, TILE_SIZE);
										xps.push_back(silver2);
									}
									// Slime
									else if (auto* scorpion = dynamic_cast<Scorpion*>(enemy)) {
										XP* bronze1 = new Bronze(scorpion->getCenter().x, scorpion->getCenter().y + 20, arena, resolution, TILE_SIZE);
										xps.push_back(bronze1);
										XP* silver1 = new Silver(scorpion->getCenter().x, scorpion->getCenter().y + 20, arena, resolution, TILE_SIZE);
										xps.push_back(silver1);
										XP* silver2 = new Silver(scorpion->getCenter().x + 20, scorpion->getCenter().y, arena, resolution, TILE_SIZE);
										xps.push_back(silver2);

									}
									// Ghost
									else if (auto* ghost = dynamic_cast<Ghost*>(enemy)) {
										XP* bronze1 = new Bronze(ghost->getCenter().x, ghost->getCenter().y, arena, resolution, TILE_SIZE);
										xps.push_back(bronze1);
										XP* bronze2 = new Bronze(ghost->getCenter().x + 20, ghost->getCenter().y, arena, resolution, TILE_SIZE);
										xps.push_back(bronze2);
									}
									// Mummy
									else if (auto* mummy = dynamic_cast<Mummy*>(enemy)) {
										XP* gold = new Gold(mummy->getCenter().x, mummy->getCenter().y + 20, arena, resolution, TILE_SIZE);
										xps.push_back(gold);
										XP* bronze1 = new Bronze(mummy->getCenter().x + 20, mummy->getCenter().y + 20, arena, resolution, TILE_SIZE);
										xps.push_back(bronze1);
										XP* silver1 = new Silver(mummy->getCenter().x + 20, mummy->getCenter().y + 50, arena, resolution, TILE_SIZE);
										xps.push_back(silver1);
										XP* silver2 = new Silver(mummy->getCenter().x + 20, mummy->getCenter().y, arena, resolution, TILE_SIZE);
										xps.push_back(silver2);
									}
								}
							}
						}
					}
				}

				for (const auto& obstacle : obstacles) {
					if (auto* rock = dynamic_cast<Wall*>(obstacle)) {
						if (bullet->getPosition().intersects(rock->getPosition()))
						{
							if (bullet->isInFlight())
							{
								bullet->stop();
							}
						}
					}
				}
			}
		}

	}// End if playing

	m_MainView.setCenter(m_fireMage.getCenter());
}

Vector2f Engine::findClosestSlimeTarget(Slime& currentSlime, const vector<Enemy*>& enemies, FireMage& player)
{
	Vector2f closestPosition;
	float closestDistance = std::numeric_limits<float>::infinity();

	// Check the distance to the player
	Vector2f playerPosition = player.getCenter();
	float playerDistance = std::sqrt(std::pow(currentSlime.getCenter().x - playerPosition.x, 2) +
		std::pow(currentSlime.getCenter().y - playerPosition.y, 2));

	if (playerDistance < closestDistance) {
		closestDistance = playerDistance;
		closestPosition = playerPosition;
	}

	// Check the distance to other slime enemies
	for (auto& enemy : enemies) {
		if (enemy->getIsAlive() && !dynamic_cast<Ghost*>(enemy)) {
			// Skip the current slime itself
			if (enemy != &currentSlime) {
				Vector2f enemyPosition = enemy->getCenter();
				float distance = std::sqrt(std::pow(currentSlime.getCenter().x - enemyPosition.x, 2) +
					std::pow(currentSlime.getCenter().y - enemyPosition.y, 2));

				if (distance < closestDistance) {
					closestDistance = distance;
					closestPosition = enemyPosition;
				}
			}
		}
	}

	return closestPosition;
}

bool Engine::isEnemyCloseToTurret(FireTurret& turret, const vector<Enemy*>& enemies)
{
	float range = turret.getRange();

	for (auto& enemy : enemies) {
		if (enemy->getIsAlive() && !dynamic_cast<Ghost*>(enemy)) {
			Vector2f enemyPosition = enemy->getCenter();
			float distance = std::sqrt(std::pow(turret.getCenter().x - enemyPosition.x, 2) +
				std::pow(turret.getCenter().y - enemyPosition.y, 2));

			if (distance < range) {
				// An enemy is close to the turret
				return true;
			}
		}
	}

	// No enemy is close to the turret
	return false;
}

Vector2f Engine::findClosestEnemyToTurret(FireTurret& turret, const vector<Enemy*>& enemies)
{
	Vector2f closestPosition;
	float closestDistance = turret.getRange();

	for (auto& enemy : enemies) {
		if (enemy->getIsAlive() && !dynamic_cast<Ghost*>(enemy)) {
			Vector2f enemyPosition = enemy->getCenter();
			float distance = std::sqrt(std::pow(turret.getCenter().x - enemyPosition.x, 2) +
				std::pow(turret.getCenter().y - enemyPosition.y, 2));

			if (distance < closestDistance) {
				closestDistance = distance;
				closestPosition = enemyPosition;
			}
		}
	}

	return closestPosition;
}


