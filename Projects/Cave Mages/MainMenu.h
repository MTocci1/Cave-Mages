#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class MainMenu
{
private:
	Font m_Font;
	Text m_PlayText;
	bool m_hoveringPlay = false;

	Text m_ExitText;
	bool m_hoveringExit = false;

	Sprite m_Logo;

public:
	MainMenu();

	Text getPlayText();

	void setHoveringPlay(bool isHovering);

	Text getExitText();

	void setHoveringExit(bool isHovering);

	Sprite getLogo();

	void update();
};