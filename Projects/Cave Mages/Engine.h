#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include "TextureHolder.h"
#include "Arena.h"
#include "fireMage.h"
#include "Dummy.h"
#include "Bullet.h"
#include "Ability.h"
#include "HUD.h"
#include "Enemy.h"
#include "Spider.h"
#include "Ghost.h"
#include "Obstacle.h"
#include "Wall.h"
#include "Water.h"
#include "HealthStation.h"
#include "ShieldStation.h"
#include "Scorpion.h"
#include "FireBullet.h"
#include "Mummy.h"
#include "MummyBullet.h"
#include "Snail.h"
#include "Mimic.h"
#include "MimicBullet.h"
#include "MimicAbility.h"
#include "Slime.h"
#include "XP.h"
#include "XP-Gold.h"
#include "XP-Bronze.h"
#include "XP-Silver.h"
#include "DeployableStation.h"
#include "Deployable.h"
#include "LifeTree.h"
#include "LifeTreeBullet.h"
#include "FireTurret.h"
#include "FireTurretBullet.h"
#include "MainMenu.h"
#include "DeployMenu.h"


using namespace sf;
using namespace std;

class Engine
{
private:
	// The texture holder
	TextureHolder th;
	const int TILE_SIZE = 100;
	const int VERTS_IN_QUAD = 4;

	// Arena Setup
	IntRect arena;
	Vector2f resolution;

	int m_WaveNumber;
	int m_StartNumberEnemies;
	int m_EnemiesLeft;

	// Is it time for a new wave?
	bool m_NewWaveRequired;


	// Create the background
	VertexArray background;
	Texture textureBackground;

	Sprite spriteCrosshair;
	Texture textureCrosshair;

	// All the mages
	FireMage m_fireMage;

	// All the enemies
	vector<Enemy*> enemies;

	// All the Obstacles
	vector<Obstacle*> obstacles;

	// All the Deployables
	vector < Deployable*> deployables;

	// All the XP
	vector<XP*> xps;

	// Dummy
	Dummy m_dummy;

	// The one Snail
	Snail m_Snail;

	// The Mimic
	Mimic m_Mimic;

	// Player Ability
	Ability m_Ability;

	// Mimic Ability
	MimicAbility m_MimicAbility;

	// The HUD
	Hud m_Hud;

	// The Main Menu
	MainMenu m_MainMenu;

	// The deploy menu
	DeployMenu m_DeployMenu;

	// Vector of bullets
	// Player Bullets
	vector<Bullet*> bullets;

	// Mummy Bullets
	vector<Bullet*> mummyBullets;

	// Mimic Bullets
	vector<Bullet*> mimicBullets;

	// Life Tree Bullets
	vector <Bullet*> lifeTreeBullets;

	//Fire Turrett Bullets
	vector <Bullet*> fireTurretBullets;

	// A regular RenderWindow
	RenderWindow m_Window;

	// The main View for character
	View m_MainView;

	// Create a view for the HUD
	View m_HudView;

	// Declare a sprite and a Texture 
	// for the background
	Sprite m_BackgroundSprite;
	Texture m_BackgroundTexture;


	// Calculate game time
	Time m_GameTimeTotal;

	// Time the player last shot
	Time m_lastShot;

	// Time the player last ability use
	Time m_lastAbility;

	// Where is the mouse in relation to world coordinates
	Vector2f mouseWorldPosition;

	// Where is the mouse in relation to screen coordinates
	Vector2i mouseScreenPosition;

	DeployableStation* m_currentDeployableStation;
	Vector2f m_deployPosition;

	// Deployable Variables
	int m_deployableStationsToSpawn;
	int turretCost;
	int treeCost;

	// GAME STATES
	// Player begins game in main menu
	bool m_inMainMenu = true;
	bool m_Playing = false;
	bool m_PickingDeployable = false;

	// Private functions for internal use only
	void input();

	void update(float dtAsSeconds);

	void draw();

	void loadWave();

	Vector2f findClosestSlimeTarget(Slime& currentSlime, const vector<Enemy*>& enemies, FireMage& player);

	Vector2f findClosestEnemyToTurret(FireTurret& turret, const vector<Enemy*>& enemies);

	bool isEnemyCloseToTurret(FireTurret& turret, const vector<Enemy*>& enemies);

public:
	// The Engine constructor
	Engine();

	// Run will call all the private functions
	void run();
};