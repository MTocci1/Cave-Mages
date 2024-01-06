#include "MainMenu.h"
#include "TextureHolder.h"

MainMenu::MainMenu()
{
	Vector2u resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	// Load the font
	m_Font.loadFromFile("fonts/impact.ttf");

	// Play Text
	m_PlayText.setFont(m_Font);
	m_PlayText.setCharacterSize(125);
	m_PlayText.setFillColor(Color::White);
	m_PlayText.setPosition(50, 50);
	m_PlayText.setString("Play");
	m_PlayText.setLetterSpacing(1.5);

	// Exit Text
	m_ExitText.setFont(m_Font);
	m_ExitText.setCharacterSize(125);
	m_ExitText.setFillColor(Color::White);
	m_ExitText.setPosition(50, 100);
	m_ExitText.setString("Exit");
	m_ExitText.setLetterSpacing(1.5);

	// Logo Icon
	// Associate a texture with the sprite
	m_Logo = Sprite(TextureHolder::GetTexture(
		"graphics/logo.png"));
	m_Logo.setScale(.40, .40);
	m_Logo.setPosition(100, resolution.y - 200);


	// Center the Main Menu items
	float playTextX = (resolution.x / 2) - (m_PlayText.getGlobalBounds().width / 2);
	float playTextY = (resolution.y / 2) - (m_PlayText.getGlobalBounds().height / 2) - 100;
	m_PlayText.setPosition(playTextX, playTextY);

	float ExitTextX = (resolution.x / 2) - (m_ExitText.getGlobalBounds().width / 2);
	float ExitTextY = (resolution.y / 2) - (m_ExitText.getGlobalBounds().height / 2) + 100;
	m_ExitText.setPosition(ExitTextX, ExitTextY);

	float logoX = (resolution.x / 2) - (m_Logo.getGlobalBounds().width / 2);
	float logoY = 100;
	m_Logo.setPosition(logoX, logoY);

}

Text MainMenu::getPlayText()
{
	return m_PlayText;
}
void MainMenu::setHoveringPlay(bool isHovering)
{
	m_hoveringPlay = isHovering;
}

Text MainMenu::getExitText()
{
	return m_ExitText;
}
void MainMenu::setHoveringExit(bool isHovering)
{
	m_hoveringExit = isHovering;
}

Sprite MainMenu::getLogo()
{
	return m_Logo;
}

void MainMenu::update()
{
	if (m_hoveringPlay) {
		m_PlayText.setFillColor(Color::Red);
	}
	else {
		m_PlayText.setFillColor(Color::White);
	}

	if (m_hoveringExit) {
		m_ExitText.setFillColor(Color::Red);
	}
	else {
		m_ExitText.setFillColor(Color::White);
	}
}

