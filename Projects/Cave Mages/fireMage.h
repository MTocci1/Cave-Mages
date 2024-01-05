#pragma once
#include "PlayableCharacter.h"

class FireMage : public PlayableCharacter
{
public:
	// A constructor specific to the fire mage
	FireMage();

	// The overriden input handler for fire mage
	void virtual handleInput();
};