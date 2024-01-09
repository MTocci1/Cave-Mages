#include "Ghost.h"
#include "TextureHolder.h"

Ghost::Ghost()
{
	// Associate a texture with the sprite
	m_Sprite = Sprite(TextureHolder::GetTexture(
		"graphics/ghost.png"));
	m_Sprite.setScale(.25, .25);

	// Load the font
	m_Font.loadFromFile("fonts/impact.ttf");

	// when Paused
	m_DamageText.setFont(m_Font);
	m_DamageText.setCharacterSize(35);
	m_DamageText.setFillColor(Color::Cyan);
	m_DamageText.setString("");

	textTimer = 0.0f;

	m_TotalDamage = 0;

	m_isAlive = true;

	m_Speed = 200;
	m_Health = 20;
	m_Damage = 0;
}

void Ghost::hitPlayer(int& enemiesLeft)
{
	m_isAlive = false;
	enemiesLeft -= 1;
}

void Ghost::update(float elapsedTime, bool playerFacingDirection, Vector2f playerPosition)
{
	if (m_isAlive) {
		// Keep the enemy in the arena
		if (m_Position.x > m_Arena.width - m_TileSize)
		{
			m_Position.x = m_Arena.width - m_TileSize;
		}
		if (m_Position.x < m_Arena.left)
		{
			m_Position.x = m_Arena.left;
		}
		if (m_Position.y > m_Arena.height - m_TileSize)
		{
			m_Position.y = m_Arena.height - m_TileSize;
		}
		if (m_Position.y < m_Arena.top)
		{
			m_Position.y = m_Arena.top;
		}

		prevPosition = m_Sprite.getPosition();
		Vector2f newPosition = prevPosition + Vector2f(elapsedTime * m_Speed, elapsedTime * m_Speed);

		m_Sprite.setPosition(m_Position);

		// Update the damage text position
		FloatRect textRect = m_DamageText.getLocalBounds();
		m_DamageText.setPosition(
			getCenter().x - textRect.width / 2,
			getCenter().y - (textRect.height / 2) - 45
		);

		m_lastHitByAbility -= elapsedTime;
		m_lastHitBySlime -= elapsedTime;

		float playerX = playerPosition.x;
		float playerY = playerPosition.y;

		// Check the direction the player is facing
		// playerFacingDirection is the bool facingLeft, if true player is facing left 
		if (playerX > m_Position.x && !playerFacingDirection)
		{
			m_Position.x = m_Position.x +
				m_Speed * elapsedTime;
		}

		if ((playerX > m_Position.x && !playerFacingDirection) || (playerX < m_Position.x && playerFacingDirection)) {
			if (playerY > m_Position.y)
			{
				m_Position.y = m_Position.y +
					m_Speed * elapsedTime;
			}
		}

		if (playerX < m_Position.x && playerFacingDirection)
		{
			m_Position.x = m_Position.x -
				m_Speed * elapsedTime;
		}

		if ((playerX > m_Position.x && !playerFacingDirection) || (playerX < m_Position.x && playerFacingDirection)) {
			if (playerY < m_Position.y)
			{
				m_Position.y = m_Position.y -
					m_Speed * elapsedTime;
			}
		}
	}

	// Only show damage text for a limited time
	textTimer -= elapsedTime;
	if (textTimer < 0.0)
	{
		m_TotalDamage = 0;
		m_DamageText.setString("");
	}
}

void Ghost::isPlayerInRange(Vector2f playerPosition)
{

}

void Ghost::setFacingDirection(bool isAimingRight)
{
	if (isAimingRight)
	{
		m_facingRight = true;
		m_facingLeft = false;

		m_Sprite.setScale(.25, .25);

		m_Sprite.setOrigin(0, 0);


	}
	else {
		m_facingRight = false;
		m_facingLeft = true;

		m_Sprite.setScale(-.25, .25);

		m_Sprite.setOrigin(m_Sprite.getLocalBounds().width, 0);
	}
}