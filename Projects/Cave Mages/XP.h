#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class XP
{
protected:
	// Where is the Enemy
	Vector2f m_Position;

	// Of course we will need a sprite
	Sprite m_Sprite;

	bool m_isSpawned;

	IntRect m_Arena;
	Vector2f m_Resolution;
	int m_TileSize;

	bool m_isPlayerInRange;

	int m_Value;

	int m_Speed;

	Vector2f prevPosition;

private:
	// And a texture
	Texture m_Texture;

public:

	// This class is now abstract and cannot be instantiated
	// Where is the XP
	FloatRect getPosition();

	// Send a copy of the sprite to main
	Sprite getSprite();

	void cancelMovement();

	bool getIsSpawned();

	// We will call this function once every frame
	virtual void update(float elapsedTime, Vector2f playerPosition) = 0;

	// Check if the player is in XP range
	virtual void isPlayerInRange(Vector2f playerPosition) = 0;

	int getValue();

	void touchedByPlayer();
};