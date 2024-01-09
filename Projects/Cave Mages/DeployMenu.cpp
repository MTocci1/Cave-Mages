#include "DeployMenu.h"
#include "TextureHolder.h"

DeployMenu::DeployMenu()
{
	Vector2u resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	// Load the font
	m_Font.loadFromFile("fonts/Crang.ttf");

	m_ChooseDeployableText.setFont(m_Font);
	m_ChooseDeployableText.setCharacterSize(100);
	m_ChooseDeployableText.setFillColor(Color::White);
	m_ChooseDeployableText.setString("Choose Deployable");
	m_ChooseDeployableText.setLetterSpacing(1.5);

	// Tree Cost Text
	m_TreeUpgradeCost.setFont(m_Font);
	m_TreeUpgradeCost.setCharacterSize(50);
	m_TreeUpgradeCost.setFillColor(Color::White);
	m_TreeUpgradeCost.setString("Play");
	m_TreeUpgradeCost.setLetterSpacing(1.5);

	// Turret Cost Text
	m_TurretUpgradeCost.setFont(m_Font);
	m_TurretUpgradeCost.setCharacterSize(50);
	m_TurretUpgradeCost.setFillColor(Color::White);
	m_TurretUpgradeCost.setString("Exit");
	m_TurretUpgradeCost.setLetterSpacing(1.5);

	// Deployable Icons
	// Associate a texture with the sprite
	m_TurretIcon = Sprite(TextureHolder::GetTexture(
		"graphics/fire-turret-icon.png"));
	m_TurretIcon.setScale(.8, .8);

	m_TreeIcon = Sprite(TextureHolder::GetTexture(
		"graphics/tree-of-life-icon.png"));
	m_TreeIcon.setScale(.8, .8);


	// Center the Main Menu items
	float TurretIconX = (resolution.x / 2) - (m_TurretIcon.getGlobalBounds().width / 2) - 100;
	float TurretIconY = (resolution.y / 2) - (m_TurretIcon.getGlobalBounds().height / 2);
	m_TurretIcon.setPosition(TurretIconX, TurretIconY);

	float TreeIconX = (resolution.x / 2) - (m_TreeIcon.getGlobalBounds().width / 2) + 100;
	float TreeIconY = (resolution.y / 2) - (m_TreeIcon.getGlobalBounds().height / 2);
	m_TreeIcon.setPosition(TreeIconX, TreeIconY);

	float ChooseDeployableTextX = (resolution.x / 2) - (m_ChooseDeployableText.getGlobalBounds().width / 2);
	float ChooseDeployableTextY = 20;
	m_ChooseDeployableText.setPosition(ChooseDeployableTextX, ChooseDeployableTextY);

}

Text DeployMenu::getChooseDeployableText()
{
	return m_ChooseDeployableText;
}

Sprite DeployMenu::getTurretIcon()
{
	return m_TurretIcon;
}

void DeployMenu::setHoveringTurretIcon(bool isHovering)
{
	m_hoveringTurretIcon = isHovering;
}

Sprite DeployMenu::getTreeIcon()
{
	return m_TreeIcon;
}

void DeployMenu::setHoveringTreeIcon(bool isHovering)
{
	m_hoveringTreeIcon = isHovering;
}

Text DeployMenu::getTurretUpgradeCost()
{
	return m_TurretUpgradeCost;
}

Text DeployMenu::getTreeUpgradeCost()
{
	return m_TreeUpgradeCost;
}

Vector2f DeployMenu::getTurretIconCenter()
{
	return Vector2f(
		m_TurretIcon.getPosition().x + m_TurretIcon.getGlobalBounds().width / 2,
		m_TurretIcon.getPosition().y + m_TurretIcon.getGlobalBounds().height / 2
	);
}

Vector2f DeployMenu::getTreeIconCenter()
{
	return Vector2f(
		m_TreeIcon.getPosition().x + m_TreeIcon.getGlobalBounds().width / 2,
		m_TreeIcon.getPosition().y + m_TreeIcon.getGlobalBounds().height / 2
	);
}

void DeployMenu::update(int turretUpgradeCost, int treeUpgradeCost)
{
	Vector2u resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	if (m_hoveringTurretIcon) {
		m_TurretIcon = Sprite(TextureHolder::GetTexture(
			"graphics/fire-turret-icon.png"));
		m_TurretIcon.setScale(.8, .8);
		float TurretIconX = (resolution.x / 2) - (m_TurretIcon.getGlobalBounds().width / 2) - 300;
		float TurretIconY = (resolution.y / 2) - (m_TurretIcon.getGlobalBounds().height / 2);
		m_TurretIcon.setPosition(TurretIconX, TurretIconY);
	}
	else {
		m_TurretIcon = Sprite(TextureHolder::GetTexture(
			"graphics/fire-turret-icon.png"));
		m_TurretIcon.setScale(.8, .8);
		float TurretIconX = (resolution.x / 2) - (m_TurretIcon.getGlobalBounds().width / 2) - 300;
		float TurretIconY = (resolution.y / 2) - (m_TurretIcon.getGlobalBounds().height / 2);
		m_TurretIcon.setPosition(TurretIconX, TurretIconY);
	}

	if (m_hoveringTreeIcon) {
		m_TreeIcon = Sprite(TextureHolder::GetTexture(
			"graphics/tree-of-life-icon.png"));
		m_TreeIcon.setScale(.8, .8);
		float TreeIconX = (resolution.x / 2) - (m_TreeIcon.getGlobalBounds().width / 2) + 300;
		float TreeIconY = (resolution.y / 2) - (m_TreeIcon.getGlobalBounds().height / 2);
		m_TreeIcon.setPosition(TreeIconX, TreeIconY);
	}
	else {
		m_TreeIcon = Sprite(TextureHolder::GetTexture(
			"graphics/tree-of-life-icon.png"));
		m_TreeIcon.setScale(.8, .8);
		float TreeIconX = (resolution.x / 2) - (m_TreeIcon.getGlobalBounds().width / 2) + 300;
		float TreeIconY = (resolution.y / 2) - (m_TreeIcon.getGlobalBounds().height / 2);
		m_TreeIcon.setPosition(TreeIconX, TreeIconY);
	}

	String turretCost = std::to_string(turretUpgradeCost);
	m_TurretUpgradeCost.setString(turretCost + " XP");

	String treeCost = std::to_string(treeUpgradeCost);
	m_TreeUpgradeCost.setString(treeCost + " XP");

	float TreeCostX = (getTreeIconCenter().x) - (m_TreeUpgradeCost.getGlobalBounds().width / 2);
	float TreeCostY = (getTreeIconCenter().y) - (m_TreeUpgradeCost.getGlobalBounds().height / 2) + 370;
	m_TreeUpgradeCost.setPosition(TreeCostX, TreeCostY);

	float TurretCostX = (getTurretIconCenter().x) - (m_TurretUpgradeCost.getGlobalBounds().width / 2);
	float TurretCostY = (getTurretIconCenter().y) - (m_TurretUpgradeCost.getGlobalBounds().height / 2) + 370;
	m_TurretUpgradeCost.setPosition(TurretCostX, TurretCostY);

}

