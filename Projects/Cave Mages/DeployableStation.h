#pragma once
#include "Obstacle.h"

class DeployableStation : public Obstacle
{
private:
	bool m_isSpawned;

	Font m_Font;
	Text m_Text;

	int m_UpgradeCost;

public:
	DeployableStation();

	void virtual spawn(IntRect arena, Vector2f resolution, int tileSize);

	void showText();

	void hideText();

	int getUpgradeCost();

	Text getText();

	void isPlayerInRange(Vector2f playerPosition);
};