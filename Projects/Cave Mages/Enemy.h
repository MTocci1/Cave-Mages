#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Enemy
{
protected:
	// Where is the Enemy
	Vector2f m_Position;

	// Of course we will need a sprite
	Sprite m_Sprite;

	// Enemy Stats
	// How fast is the enemy
	float m_Speed;
	int m_Health;

	bool m_isAlive;

	int m_Damage;

	Vector2f prevPosition;

	IntRect m_Arena;
	Vector2f m_Resolution;
	int m_TileSize;

	// Enemy will display damage taken when hit
	Font m_Font;
	Text m_DamageText;

	int m_TotalDamage;

	float textTimer;

	float m_lastHitByAbility;

	float m_lastHitBySlime;

	bool m_isPlayerInRange;

	bool m_isOnWater = false;

	float m_SpeedOnWater;

	// Keep Track of where the enemy is facing
	bool m_facingLeft;
	bool m_facingRight;

private:
	// And a texture
	Texture m_Texture;

public:
	void spawn(IntRect arena, Vector2f resolution, int tileSize);

	// This class is now abstract and cannot be instantiated
	// Where is the enemy
	FloatRect getPosition();

	// Send a copy of the sprite to main
	Sprite getSprite();

	// Where is the center of the enemy
	Vector2f getCenter();

	Text getText();

	// We will call this function once every frame
	virtual void update(float elapsedTime, bool playerFacingDirection, Vector2f playerPosition) = 0;

	// Check if the player is in enemy range
	virtual void isPlayerInRange(Vector2f playerPosition) = 0;

	bool hit(int damage, int& enemiesLeft);

	bool hitByAbility(int damage, int& enemiesLeft);

	bool hitBySlime(int damage, int& enemiesLeft);

	void cancelMovement();

	int getDamage();

	int getHealth();

	bool getIsAlive();

	void setIsOnWater(bool isSpiderOnWater);

	virtual void setFacingDirection(bool isAimingRight) = 0;

	bool getFacingDirection();
};// End of the class