#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class CharacterSelect
{
private:
	Font m_Font;

	Sprite m_FireMageIcon;
	bool m_hoveringFireMageIcon = false;

	Sprite m_WaterMageIcon;
	bool m_hoveringWaterMageIcon = false;

	Sprite m_UnknownIcon;

	Text m_ChooseCharacterText;

public:
	CharacterSelect();

	Text getChooseCharacterText();

	Sprite getFireMageIcon();

	void setHoveringFireMageIcon(bool isHovering);

	Sprite getWaterMageIcon();

	void setHoveringWaterMageIcon(bool isHovering);

	Sprite getUnknownIcon();

	Vector2f getFireMageIconCenter();

	Vector2f getWaterMageIconCenter();

	Vector2f getUnknownIconCenter();

	void update();
};