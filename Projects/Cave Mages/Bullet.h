#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Bullet
{
protected:
	// Of course we will need a sprite
	Sprite m_Sprite;

	// Where is the bullet?
	Vector2f m_Position;

	// Is this bullet currently whizzing through the air
	bool m_InFlight = false;

	// How fast does a bullet travel?
	float m_BulletSpeed = 1000;

	// What fraction of 1 pixel does the bullet travel, 
	// Horizontally and vertically each frame?
	// These values will be derived from m_BulletSpeed
	float m_BulletDistanceX;
	float m_BulletDistanceY;

	// Some boundaries so the bullet doesn't fly forever
	float m_MaxX;
	float m_MinX;
	float m_MaxY;
	float m_MinY;

private:
	

	// Public function prototypes go here
public:

	// Stop the bullet
	void stop();

	// Returns the value of m_InFlight
	bool isInFlight();

	// Launch a new bullet
	virtual void shoot(float startX, float startY, float xTarget, float yTarget, int multishotLevel) = 0;

	// Tell the calling code where the bullet is in the world
	FloatRect getPosition();

	// Send a copy of the sprite to main
	Sprite getSprite();

	// Update the bullet each frame
	void update(float elapsedTime);
};