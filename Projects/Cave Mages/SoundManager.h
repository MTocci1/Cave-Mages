#pragma once
#include <SFML/Audio.hpp>

using namespace sf;

class SoundManager
{
private:
	// The buffers
	SoundBuffer m_FireBulletBuffer;
	SoundBuffer m_FireBulletImpactBuffer;
	SoundBuffer m_FireAbilityBuffer;
	SoundBuffer m_DeathBuffer;
	SoundBuffer m_GameMusicBuffer;
	SoundBuffer m_MenuMusicBuffer;
	SoundBuffer m_SelectTabBuffer;
	SoundBuffer m_SlimeBuffer;
	SoundBuffer m_SpiderHissBuffer;

	// The Sounds
	Sound m_FireBulletSound;
	Sound m_FireBulletImpactSound;
	Sound m_FireAbilitySound;
	Sound m_DeathSound;
	Sound m_GameMusicSound;
	Sound m_MenuMusicSound;
	Sound m_SelectTabSound;
	Sound m_SlimeSound;
	Sound m_SpiderHissSound;

	Vector2f m_ListenerLocation;

public:
	SoundManager();

	void playFireBullet(Vector2f emitterLocation);

	void playFireBulletImpact(Vector2f emitterLocation);

	void playFireAbility();

	void stopFireAbility();

	void playGameMusic();

	void stopGameMusic();

	void playMenuMusic();

	void stopMenuMusic();

	void playSelectTab();

	void playDeathSound();

	void playSlimeSound(Vector2f emitterLocation);

	void playSpiderHiss(Vector2f emitterLocation);

	void update(Vector2f listenerLocation);
};