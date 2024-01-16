#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Snail {
private:
	// Which directions is the spider currently moving in
	bool m_LeftPressed;
	bool m_RightPressed;
	bool m_UpPressed;
	bool m_DownPressed;

	// Where is the Snail
	Vector2f m_Position;

	// Of course we will need a sprite
	Sprite m_Sprite;

	// Enemy Stats
	// How fast is the enemy
	float m_Speed;

	bool m_isAlive;

	Vector2f prevPosition;

	IntRect m_Arena;
	Vector2f m_Resolution;
	int m_TileSize;

	bool m_isOnWater = false;

	float m_SpeedOnWater;

	// And a texture
	Texture m_Texture;

	// Keep Track of where the enemy is facing
	bool m_facingLeft;
	bool m_facingRight;

public:
	Snail();

	void spawn(IntRect arena, Vector2f resolution, int tileSize);

	// This class is now abstract and cannot be instantiated
	// Where is the enemy
	FloatRect getPosition();

	// Send a copy of the sprite to main
	Sprite getSprite();

	// Where is the center of the enemy
	Vector2f getCenter();

	void update(float elapsedTime, bool playerFacingDirection, Vector2f playerPosition);

	void cancelMovement();

	void setIsOnWater(bool isSpiderOnWater);

	void setFacingDirection(bool isAimingRight);

	bool getFacingDirection();
};