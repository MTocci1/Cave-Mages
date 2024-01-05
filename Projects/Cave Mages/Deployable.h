#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Deployable
{
protected:
	// Where is the deployable
	Vector2f m_Position;

	// Of course we will need a sprite
	Sprite m_Sprite;

	bool m_isSpawned;

	IntRect m_Arena;
	Vector2f m_Resolution;
	int m_TileSize;

private:
	// And a texture
	Texture m_Texture;

public:

	// This class is now abstract and cannot be instantiated
	// Where is the deployable
	FloatRect getPosition();

	// Send a copy of the sprite to main
	Sprite getSprite();

	// Where is the center of the deployable
	Vector2f getCenter();

	// We will call this function once every frame
	virtual void update(float elapsedTime, Vector2f targetPosition) = 0;

	bool getIsSpawned();

};