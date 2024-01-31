#include "CharacterSelection.h"
#include "TextureHolder.h"

CharacterSelect::CharacterSelect()
{
	Vector2u resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	// Load the font
	m_Font.loadFromFile("fonts/Crang.ttf");

	m_ChooseCharacterText.setFont(m_Font);
	m_ChooseCharacterText.setCharacterSize(100);
	m_ChooseCharacterText.setFillColor(Color::White);
	m_ChooseCharacterText.setString("Choose Character");
	m_ChooseCharacterText.setLetterSpacing(1.5);

	// Deployable Icons
	// Associate a texture with the sprite
	m_FireMageIcon = Sprite(TextureHolder::GetTexture(
		"graphics/character-select-fire-mage.png"));
	m_FireMageIcon.setScale(.6, .6);

	m_WaterMageIcon = Sprite(TextureHolder::GetTexture(
		"graphics/character-select-water-mage.png"));
	m_WaterMageIcon.setScale(.6, .6);

	m_UnknownIcon = Sprite(TextureHolder::GetTexture(
		"graphics/character-select-unknown.png"));
	m_UnknownIcon.setScale(.6, .6);


	// Center the Main Menu items
	float FireMageIconX = (resolution.x / 2) - (m_FireMageIcon.getGlobalBounds().width / 2);
	float FireMageIconY = (resolution.y / 2) - (m_FireMageIcon.getGlobalBounds().height / 2);
	m_FireMageIcon.setPosition(FireMageIconX, FireMageIconY);

	float WaterMageIconX = (resolution.x / 2) - (m_WaterMageIcon.getGlobalBounds().width / 2);
	float WaterMageIconY = (resolution.y / 2) - (m_WaterMageIcon.getGlobalBounds().height / 2);
	m_WaterMageIcon.setPosition(WaterMageIconX, WaterMageIconY);

	float UnknownIconX = (resolution.x / 2) - (m_UnknownIcon.getGlobalBounds().width / 2) + 550;
	float UnknownIconY = (resolution.y / 2) - (m_UnknownIcon.getGlobalBounds().height / 2);
	m_UnknownIcon.setPosition(UnknownIconX, UnknownIconY);

	float ChooseCharacterTextX = (resolution.x / 2) - (m_ChooseCharacterText.getGlobalBounds().width / 2);
	float ChooseCharacterTextY = 20;
	m_ChooseCharacterText.setPosition(ChooseCharacterTextX, ChooseCharacterTextY);

}

Text CharacterSelect::getChooseCharacterText()
{
	return m_ChooseCharacterText;
}

Sprite CharacterSelect::getFireMageIcon()
{
	return m_FireMageIcon;
}

void CharacterSelect::setHoveringFireMageIcon(bool isHovering)
{
	m_hoveringFireMageIcon = isHovering;
}

Sprite CharacterSelect::getWaterMageIcon()
{
	return m_WaterMageIcon;
}

void CharacterSelect::setHoveringWaterMageIcon(bool isHovering)
{
	m_hoveringWaterMageIcon = isHovering;
}

Sprite CharacterSelect::getUnknownIcon()
{
	return m_UnknownIcon;
}

Vector2f CharacterSelect::getFireMageIconCenter()
{
	return Vector2f(
		m_FireMageIcon.getPosition().x + m_FireMageIcon.getGlobalBounds().width / 2,
		m_FireMageIcon.getPosition().y + m_FireMageIcon.getGlobalBounds().height / 2
	);
}

Vector2f CharacterSelect::getWaterMageIconCenter()
{
	return Vector2f(
		m_WaterMageIcon.getPosition().x + m_WaterMageIcon.getGlobalBounds().width / 2,
		m_WaterMageIcon.getPosition().y + m_WaterMageIcon.getGlobalBounds().height / 2
	);
}

Vector2f CharacterSelect::getUnknownIconCenter()
{
	return Vector2f(
		m_UnknownIcon.getPosition().x + m_UnknownIcon.getGlobalBounds().width / 2,
		m_UnknownIcon.getPosition().y + m_UnknownIcon.getGlobalBounds().height / 2
	);
}

void CharacterSelect::update()
{
	Vector2u resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	if (m_hoveringFireMageIcon) {
		m_FireMageIcon = Sprite(TextureHolder::GetTexture(
			"graphics/character-select-fire-mage.png"));
		m_FireMageIcon.setScale(.6, .6);
		float FireMageIconX = (resolution.x / 2) - (m_FireMageIcon.getGlobalBounds().width / 2) - 550;
		float FireMageIconY = (resolution.y / 2) - (m_FireMageIcon.getGlobalBounds().height / 2);
		m_FireMageIcon.setPosition(FireMageIconX, FireMageIconY);
	}
	else {
		m_FireMageIcon = Sprite(TextureHolder::GetTexture(
			"graphics/character-select-fire-mage.png"));
		m_FireMageIcon.setScale(.6, .6);
		float FireMageIconX = (resolution.x / 2) - (m_FireMageIcon.getGlobalBounds().width / 2) - 550;
		float FireMageIconY = (resolution.y / 2) - (m_FireMageIcon.getGlobalBounds().height / 2);
		m_FireMageIcon.setPosition(FireMageIconX, FireMageIconY);
	}

	if (m_hoveringWaterMageIcon) {
		m_WaterMageIcon = Sprite(TextureHolder::GetTexture(
			"graphics/character-select-water-mage.png"));
		m_WaterMageIcon.setScale(.6, .6);
		float WaterMageIconX = (resolution.x / 2) - (m_WaterMageIcon.getGlobalBounds().width / 2);
		float WaterMageIconY = (resolution.y / 2) - (m_WaterMageIcon.getGlobalBounds().height / 2);
		m_WaterMageIcon.setPosition(WaterMageIconX, WaterMageIconY);
	}
	else {
		m_WaterMageIcon = Sprite(TextureHolder::GetTexture(
			"graphics/character-select-water-mage.png"));
		m_WaterMageIcon.setScale(.6, .6);
		float WaterMageIconX = (resolution.x / 2) - (m_WaterMageIcon.getGlobalBounds().width / 2);
		float WaterMageIconY = (resolution.y / 2) - (m_WaterMageIcon.getGlobalBounds().height / 2);
		m_WaterMageIcon.setPosition(WaterMageIconX, WaterMageIconY);
	}
}

