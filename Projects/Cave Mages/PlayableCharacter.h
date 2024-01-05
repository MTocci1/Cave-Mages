#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class PlayableCharacter
{
protected:
	// Of course we will need a sprite
	Sprite m_Sprite;

	// Where is the player
	Vector2f m_Position;

	// Which directions is the character currently moving in
	bool m_LeftPressed;
	bool m_RightPressed;
	bool m_UpPressed;
	bool m_DownPressed;

	// Keep Track of where the player is facing
	bool m_facingLeft;
	bool m_facingRight;

	// Player Stats
	// How fast is the character
	float m_Speed;
	float m_SpeedOnWater;

	int m_Health;
	int m_MaxHealth;
	int m_Shield;
	int m_MaxShield;

	// Shoot variables
	float m_FireRate;
	int m_Damage;

	// Dash variables
	bool m_canDash;
	float m_dashCooldown;
	int m_dashDistance;

	// Ability variables
	float m_abilityCooldown;
	float m_abilityActiveTime;
	int m_abilityDamage;
	bool m_canUseAbility;
	float m_RealTimeAbilityCooldown;

	void dash();

	// Ghost effects
	bool m_isPossessed;
	float m_PossessedActiveTime;

	//Poison effects
	bool m_isPoisoned;
	float m_PoisonActiveTime;
	int m_poisonDamage;

	// Station variables
	bool m_canHeal;
	float m_healCooldown;
	int m_healAmount;

	bool m_canShield;
	float m_shieldCooldown;
	int m_shieldAmount;

private:
	// And a texture
	Texture m_Texture;

	bool m_Spawned = false;

	Vector2f prevPosition;

	float lerp(float position, float target, float lerpFactor);

	IntRect m_Arena;
	Vector2f m_Resolution;
	int m_TileSize;

	bool m_isOnWater = false;

	int m_XP;

public:
	void spawn(IntRect arena, Vector2f resolution, int tileSize);

	// This is a pure virtual function
	void virtual handleInput() = 0;

	// This class is now abstract and cannot be instantiated
	// Where is the player
	FloatRect getPosition();

	// Send a copy of the sprite to main
	Sprite getSprite();

	// Where is the center of the character
	Vector2f getCenter();

	// We will call this function once every frame
	void update(float elapsedTime);

	bool isSpawned();

	void setSpawn(bool spawn);

	void cancelMovement();

	float getFireRate();

	int getDamage();

	int getSpeed();

	bool getFacingDirection();

	int getHealth();
	int getShield();

	float getAbilityCooldown();
	float getAbilityActiveTime();
	int getAbilityDamage();
	float getRealTimeAbilityCooldown();

	float getDashCooldown();

	bool getIsOnWater();

	int getXP();

	void touchedXP(int value);

	void activatePossession();

	void activatePoison();

	void setIsOnWater(bool isPlayerOnWater);

	void healthStationHeal();

	void shieldStationHeal();

	void heal(int amount);

	void shield(int amount);

	void startAbilityCooldown();

};// End of the class