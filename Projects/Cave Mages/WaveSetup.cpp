#include "Engine.h"
#include <iostream>

void Engine::loadWave()
{
    player->spawn(arena, resolution, TILE_SIZE);

    if (m_WaveNumber != 2) {
        // Calculate how many enemies to spawn
        int enemiesToSpawn = m_StartNumberEnemies + (m_WaveNumber * 5);

        // Set the percentage chance for spiders (35%), ghosts (20%), mummies (10%), scorpions (20%), and slime (15%)
        int spiderChance = 35;
        int ghostChance = 20;
        int mummyChance = 10;
        int scorpionChance = 20;
        int slimeChance = 15;

        // Random number generation for enemies
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> distrib(1, 100);

        for (int i = 0; i < enemiesToSpawn; ++i) {
            // Decide which enemy to spawn based on the random percentage
            int randomPercentage = distrib(gen);

            if (randomPercentage <= spiderChance) {
                // Spawn a Spider
                Enemy* spider = new Spider();
                enemies.push_back(spider);
            }
            else if (randomPercentage <= spiderChance + ghostChance) {
                // Spawn a Ghost
                Enemy* ghost = new Ghost();
                enemies.push_back(ghost);
            }
            else if (randomPercentage <= spiderChance + ghostChance + mummyChance) {
                // Spawn a Mummy
                Enemy* mummy = new Mummy();
                enemies.push_back(mummy);
            }
            else if (randomPercentage <= spiderChance + ghostChance + mummyChance + scorpionChance) {
                // Spawn a Scorpion
                Enemy* scorpion = new Scorpion();
                enemies.push_back(scorpion);
            }
            else {
                // Spawn a Slime
                Enemy* slime = new Slime();
                enemies.push_back(slime);
            }
        }

        // Update the number of enemies left
        m_EnemiesLeft = enemiesToSpawn;


        // Set up the obstacles
        // Random number generation for rocks
        random_device rdWalls;
        mt19937 genWalls(rdWalls());
        uniform_int_distribution<int> distribWalls(10, 20); // 10-20 walls

        // Random number generation for water
        random_device rdWaters;
        mt19937 genWaters(rdWaters());
        uniform_int_distribution<int> distribWaters(1, 2); // 1-2 waters

        // Create walls (10-20)
        int wallsToSpawn = distribWalls(genWalls);
        for (int i = 0; i < wallsToSpawn; ++i) {
            Obstacle* wall = new Wall();
            obstacles.push_back(wall);
        }
        cout << "Spawned " << wallsToSpawn << " walls" << endl;

        // Create water (1-2)
        int watersToSpawn = distribWaters(genWaters);
        for (int i = 0; i < watersToSpawn; ++i) {
            Obstacle* water = new Water();
            obstacles.push_back(water);
        }
        cout << "Spawned " << watersToSpawn << " waters" << endl;

        // Create Stations
        // Health Station
        HealthStation* healthStation = new HealthStation();
        obstacles.push_back(healthStation);
        //Shield Station
        ShieldStation* shieldStation = new ShieldStation();
        obstacles.push_back(shieldStation);
        // Create Deployable Stations (3)
        for (int i = 0; i < m_deployableStationsToSpawn; ++i) {
            Obstacle* deployable = new DeployableStation();
            obstacles.push_back(deployable);
        }

        // Spawn Everything
        // Spawn Enemies
        for (const auto& enemy : enemies) {
            enemy->spawn(arena, resolution, TILE_SIZE);
        }
        // Spawn Obstacles
        for (const auto& obstacle : obstacles) {
            obstacle->spawn(arena, resolution, TILE_SIZE);
        }
        // Spawn Dummy
        m_dummy.spawn(arena, resolution, TILE_SIZE);
        // Spawn Snail
        m_Snail.spawn(arena, resolution, TILE_SIZE);


        // Make sure nothing spawns on top of each other
        // Loop until no intersections
        while (true) {
            bool intersectFound = false;

            // Check for enemy-enemy intersections
            for (Enemy* enemy1 : enemies) {
                for (Enemy* enemy2 : enemies) {
                    if (enemy1 != enemy2 && enemy1->getPosition().intersects(enemy2->getPosition())) {
                        intersectFound = true;
                        // Respawn an enemy
                        enemy1->spawn(arena, resolution, TILE_SIZE);
                        // Restart the loop to check for intersections again
                        intersectFound = false;
                        break;
                    }
                }
                if (intersectFound) {
                    break;
                }
            }

            // Check for obstacle-obstacle intersections
            for (Obstacle* obstacle1 : obstacles) {
                for (Obstacle* obstacle2 : obstacles) {
                    if (obstacle1 != obstacle2 && obstacle1->getPosition().intersects(obstacle2->getPosition())) {
                        intersectFound = true;
                        // Spawn a new obstacle or handle the intersection as needed
                        obstacle1->spawn(arena, resolution, TILE_SIZE);
                        // Restart the loop to check for intersections again
                        intersectFound = false;
                        break;
                    }
                }
                if (intersectFound) {
                    break;
                }
            }

            // Check for enemy-obstacle intersections
            for (Enemy* enemy : enemies) {
                for (Obstacle* obstacle : obstacles) {
                    if (enemy->getPosition().intersects(obstacle->getPosition())) {
                        intersectFound = true;
                        // Spawn a new enemy or obstacle or handle the intersection as needed
                        enemy->spawn(arena, resolution, TILE_SIZE);
                        // Restart the loop to check for intersections again
                        intersectFound = false;
                        break;
                    }
                }
                if (intersectFound) {
                    break;
                }
            }

            // Check for enemy-deployable intersections
            for (Enemy* enemy : enemies) {
                for (Deployable* deployable : deployables) {
                    if (enemy->getPosition().intersects(deployable->getPosition())) {
                        intersectFound = true;
                        // Spawn a new enemy or obstacle or handle the intersection as needed
                        enemy->spawn(arena, resolution, TILE_SIZE);
                        // Restart the loop to check for intersections again
                        intersectFound = false;
                        break;
                    }
                }
                if (intersectFound) {
                    break;
                }
            }

            // Check for obstacle-deployable intersections
            for (Obstacle* obstacle : obstacles) {
                for (Deployable* deployable : deployables) {
                    if (obstacle->getPosition().intersects(deployable->getPosition())) {
                        intersectFound = true;
                        // Spawn a new enemy or obstacle or handle the intersection as needed
                        obstacle->spawn(arena, resolution, TILE_SIZE);
                        // Restart the loop to check for intersections again
                        intersectFound = false;
                        break;
                    }
                }
                if (intersectFound) {
                    break;
                }
            }

            // Check for dummy-enemy intersections
            for (Enemy* enemy : enemies) {
                if (m_dummy.getPosition().intersects(enemy->getPosition())) {
                    intersectFound = true;
                    // Handle the intersection as needed, e.g., respawn m_dummy
                    m_dummy.spawn(arena, resolution, TILE_SIZE);
                    // Restart the loop to check for intersections again
                    intersectFound = false;
                    break;
                }
            }

            // Check for dummy-obstacle intersections
            for (Obstacle* obstacle : obstacles) {
                if (m_dummy.getPosition().intersects(obstacle->getPosition())) {
                    intersectFound = true;
                    // Handle the intersection as needed, e.g., respawn m_dummy
                    m_dummy.spawn(arena, resolution, TILE_SIZE);
                    // Restart the loop to check for intersections again
                    intersectFound = false;
                    break;
                }
            }

            // Check for dummy-deployable intersections
            for (Deployable* deployable : deployables) {
                if (m_dummy.getPosition().intersects(deployable->getPosition())) {
                    intersectFound = true;
                    // Handle the intersection as needed, e.g., respawn m_dummy
                    m_dummy.spawn(arena, resolution, TILE_SIZE);
                    // Restart the loop to check for intersections again
                    intersectFound = false;
                    break;
                }
            }

            // Check for snail-enemy intersections
            for (Enemy* enemy : enemies) {
                if (m_Snail.getPosition().intersects(enemy->getPosition())) {
                    intersectFound = true;
                    // Handle the intersection as needed, e.g., respawn m_Snail
                    m_Snail.spawn(arena, resolution, TILE_SIZE);
                    // Restart the loop to check for intersections again
                    intersectFound = false;
                    break;
                }
            }

            // Check for snail-obstacle intersections
            for (Obstacle* obstacle : obstacles) {
                if (m_Snail.getPosition().intersects(obstacle->getPosition())) {
                    intersectFound = true;
                    // Handle the intersection as needed, e.g., respawn m_Snail
                    m_Snail.spawn(arena, resolution, TILE_SIZE);
                    // Restart the loop to check for intersections again
                    intersectFound = false;
                    break;
                }
            }

            // Check for snail-deployable intersections
            for (Deployable* deployable : deployables) {
                if (m_Snail.getPosition().intersects(deployable->getPosition())) {
                    intersectFound = true;
                    // Handle the intersection as needed, e.g., respawn m_Snail
                    m_Snail.spawn(arena, resolution, TILE_SIZE);
                    // Restart the loop to check for intersections again
                    intersectFound = false;
                    break;
                }
            }

            // Check for snail-dummy intersection
            if (m_Snail.getPosition().intersects(m_dummy.getPosition())) {
                intersectFound = true;
                // Handle the intersection as needed, e.g., respawn m_Snail
                m_Snail.spawn(arena, resolution, TILE_SIZE);
                // Restart the loop to check for intersections again
                intersectFound = false;
            }

            // If no intersections found, exit the loop
            if (!intersectFound) {
                break;
            }
        }
    }


    if (m_WaveNumber == 2) 
    {
        m_Mimic.setup(player->getFireRate(), player->getSpeed(), player->getDamage(), player->getAbilityCooldown(),
            player->getAbilityActiveTime(), player->getAbilityDamage(), arena, resolution, TILE_SIZE);

        // Update the number of enemies left
        m_EnemiesLeft = 1;

        // Set up the obstacles
        // Random number generation for rocks
        random_device rdWalls;
        mt19937 genWalls(rdWalls());
        uniform_int_distribution<int> distribWalls(5, 10); // 5-10 walls

        // Random number generation for water
        random_device rdWaters;
        mt19937 genWaters(rdWaters());
        uniform_int_distribution<int> distribWaters(0, 1); // 1-2 waters

        // Create walls (5-10)
        int wallsToSpawn = distribWalls(genWalls);
        for (int i = 0; i < wallsToSpawn; ++i) {
            Obstacle* wall = new Wall();
            obstacles.push_back(wall);
        }
        cout << "Spawned " << wallsToSpawn << " walls" << endl;

        // Create water (0-1)
        int watersToSpawn = distribWaters(genWaters);
        for (int i = 0; i < watersToSpawn; ++i) {
            Obstacle* water = new Water();
            obstacles.push_back(water);
        }
        cout << "Spawned " << watersToSpawn << " waters" << endl;

        // Spawn Everything
        // Spawn Obstacles
        for (const auto& obstacle : obstacles) {
            obstacle->spawn(arena, resolution, TILE_SIZE);
        }
        // Spawn Dummy
        m_dummy.spawn(arena, resolution, TILE_SIZE);
        // Spawn Snail
        m_Snail.spawn(arena, resolution, TILE_SIZE);


        // Make sure nothing spawns on top of each other
        // Loop until no intersections
        while (true) {
            bool intersectFound = false;

            // Check for obstacle-obstacle intersections
            for (Obstacle* obstacle1 : obstacles) {
                for (Obstacle* obstacle2 : obstacles) {
                    if (obstacle1 != obstacle2 && obstacle1->getPosition().intersects(obstacle2->getPosition())) {
                        intersectFound = true;
                        // Spawn a new obstacle or handle the intersection as needed
                        obstacle1->spawn(arena, resolution, TILE_SIZE);
                        // Restart the loop to check for intersections again
                        intersectFound = false;
                        break;
                    }
                }
                if (intersectFound) {
                    break;
                }
            }

            // Check for obstacle-deployable intersections
            for (Obstacle* obstacle : obstacles) {
                for (Deployable* deployable : deployables) {
                    if (obstacle->getPosition().intersects(deployable->getPosition())) {
                        intersectFound = true;
                        // Spawn a new enemy or obstacle or handle the intersection as needed
                        obstacle->spawn(arena, resolution, TILE_SIZE);
                        // Restart the loop to check for intersections again
                        intersectFound = false;
                        break;
                    }
                }
                if (intersectFound) {
                    break;
                }
            }

            // Check for dummy-obstacle intersections
            for (Obstacle* obstacle : obstacles) {
                if (m_dummy.getPosition().intersects(obstacle->getPosition())) {
                    intersectFound = true;
                    // Handle the intersection as needed, e.g., respawn m_dummy
                    m_dummy.spawn(arena, resolution, TILE_SIZE);
                    // Restart the loop to check for intersections again
                    intersectFound = false;
                    break;
                }
            }

            // Check for dummy-deployable intersections
            for (Deployable* deployable : deployables) {
                if (m_dummy.getPosition().intersects(deployable->getPosition())) {
                    intersectFound = true;
                    // Handle the intersection as needed, e.g., respawn m_dummy
                    m_dummy.spawn(arena, resolution, TILE_SIZE);
                    // Restart the loop to check for intersections again
                    intersectFound = false;
                    break;
                }
            }

            // Check for snail-obstacle intersections
            for (Obstacle* obstacle : obstacles) {
                if (m_Snail.getPosition().intersects(obstacle->getPosition())) {
                    intersectFound = true;
                    // Handle the intersection as needed, e.g., respawn m_Snail
                    m_Snail.spawn(arena, resolution, TILE_SIZE);
                    // Restart the loop to check for intersections again
                    intersectFound = false;
                    break;
                }
            }

            // Check for snail-deployable intersections
            for (Deployable* deployable : deployables) {
                if (m_Snail.getPosition().intersects(deployable->getPosition())) {
                    intersectFound = true;
                    // Handle the intersection as needed, e.g., respawn m_Snail
                    m_Snail.spawn(arena, resolution, TILE_SIZE);
                    // Restart the loop to check for intersections again
                    intersectFound = false;
                    break;
                }
            }

            // Check for snail-dummy intersection
            if (m_Snail.getPosition().intersects(m_dummy.getPosition())) {
                intersectFound = true;
                // Handle the intersection as needed, e.g., respawn m_Snail
                m_Snail.spawn(arena, resolution, TILE_SIZE);
                // Restart the loop to check for intersections again
                intersectFound = false;
            }

            // Check for mimic-obstacle intersections
            for (Obstacle* obstacle : obstacles) {
                if (m_Mimic.getPosition().intersects(obstacle->getPosition())) {
                    intersectFound = true;
                    // Handle the intersection as needed, e.g., reposition or respawn m_Mimic
                    obstacle->spawn(arena, resolution, TILE_SIZE);
                    // Restart the loop to check for intersections again
                    intersectFound = false;
                    break;
                }
            }

            // Check for mimic-dummy intersection
            if (m_Mimic.getPosition().intersects(m_dummy.getPosition())) {
                intersectFound = true;
                // Handle the intersection as needed, e.g., respawn m_Snail
                m_dummy.spawn(arena, resolution, TILE_SIZE);
                // Restart the loop to check for intersections again
                intersectFound = false;
            }

            // Check for mimic-snail intersection
            if (m_Mimic.getPosition().intersects(m_Snail.getPosition())) {
                intersectFound = true;
                // Handle the intersection as needed, e.g., respawn m_Snail
                m_Snail.spawn(arena, resolution, TILE_SIZE);
                // Restart the loop to check for intersections again
                intersectFound = false;
            }

            // If no intersections found, exit the loop
            if (!intersectFound) {
                break;
            }
        }
    }

    m_NewWaveRequired = false;
}