#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class DeployMenu
{
private:
	Font m_Font;

	Sprite m_TurretIcon;
	bool m_hoveringTurretIcon = false;
	Text m_TurretUpgradeCost;

	Sprite m_TreeIcon;
	bool m_hoveringTreeIcon = false;
	Text m_TreeUpgradeCost;

	Text m_ChooseDeployableText;

public:
	DeployMenu();

	Text getChooseDeployableText();

	Sprite getTurretIcon();

	void setHoveringTurretIcon(bool isHovering);

	Sprite getTreeIcon();

	void setHoveringTreeIcon(bool isHovering);

	Text getTurretUpgradeCost();

	Text getTreeUpgradeCost();

	Vector2f getTurretIconCenter();

	Vector2f getTreeIconCenter();

	void update(int turretUpgradeCost, int treeUpgradeCost);
};