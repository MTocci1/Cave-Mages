#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Obstacle
{
protected:
	// The sprite that represents this pickup
	Sprite m_Sprite;

	// Where is the obstacle
	Vector2f m_Position;

	// The arena it exists in
	IntRect m_Arena;
	Vector2f m_Resolution;
	int m_TileSize;

private:

	// Handle spawning and disappearing
	bool m_Spawned;


	// Public prototypes go here
public:

	virtual void spawn(IntRect arena, Vector2f resolution, int tileSize) = 0;

	// Check the position of a wall
	FloatRect getPosition();

	// Get the sprite for drawing
	Sprite getSprite();

	Vector2f getCenter();

	// Update the obstacle
	virtual void update(float elapsedTime);

	// Is this pickup currently spawned?
	bool isSpawned();

	FloatRect getCollider() const;

	void despawn();

};