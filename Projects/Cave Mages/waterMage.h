#pragma once
#include "PlayableCharacter.h"

class WaterMage : public PlayableCharacter
{
public:
	// A constructor specific to the fire mage
	WaterMage();

	// The overriden input handler for fire mage
	void virtual handleInput();
};