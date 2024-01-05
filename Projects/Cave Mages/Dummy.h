#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Dummy
{
private:
	// Where is the player
	Vector2f m_Position;

	// And a texture
	Texture m_Texture;

	bool m_Spawned = false;

	// Of course we will need a sprite
	Sprite m_Sprite;

	// Dummy will display damage taken when hit
	Font m_Font;
	Text m_DamageText;

	int m_TotalDamage;

	int m_TotalGameDamage;

	float textTimer;

	float m_lastHitByAbility;

	IntRect m_Arena;
	Vector2f m_Resolution;
	int m_TileSize;

public:
	Dummy();

	void spawn(IntRect arena, Vector2f resolution, int tileSize);

	// This class is now abstract and cannot be instantiated
	// Where is the player
	FloatRect getPosition();

	// Send a copy of the sprite to main
	Sprite getSprite();

	// Where is the center of the character
	Vector2f getCenter();

	Text getText();

	// We will call this function once every frame
	void update(float elapsedTime);

	void hit(int damage);

	void hitByAbility(int damage);

	bool isSpawned();

	void setSpawn(bool spawn);

};// End of the class