#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class MimicAbility
{
private:
	// Of course we will need a sprite
	Sprite m_Sprite;

	// Where is the ability?
	Vector2f m_Position;

	// Is this ability currently active
	bool m_Active = false;

	float m_timeActive;

	// Public function prototypes go here
public:
	// The constructor
	MimicAbility();

	// Stop the ability
	void stop();

	// Returns the value of m_InFlight
	bool isActive();

	// Launch a new ability
	void activate(float timeActive);

	// Tell the calling code where the ablity is in the world
	FloatRect getPosition();

	// Send a copy of the sprite to main
	Sprite getSprite();

	// Update the ability each frame
	void update(float elapsedTime, float playerX, float playerY);
};