#include "SoundManager.h"
#include <SFML/Audio.hpp>

using namespace sf;

SoundManager::SoundManager()
{
	// Load the sounds
	m_FireBulletBuffer.loadFromFile("sound/fire-bullet.mp3");
	m_FireBulletImpactBuffer.loadFromFile("sound/fire-bullet-impact.mp3");
	m_FireAbilityBuffer.loadFromFile("sound/fire-ability.mp3");
	m_DeathBuffer.loadFromFile("sound/death-sound.mp3");
	m_GameMusicBuffer.loadFromFile("sound/game-music.mp3");
	m_MenuMusicBuffer.loadFromFile("sound/menu-music.mp3");
	m_SelectTabBuffer.loadFromFile("sound/select-tab.mp3");
	m_SlimeBuffer.loadFromFile("sound/slime.mp3");
	m_SpiderHissBuffer.loadFromFile("sound/spider-hiss.mp3");

	m_FireBulletSound.setBuffer(m_FireBulletBuffer);
	m_FireBulletImpactSound.setBuffer(m_FireBulletImpactBuffer);
	m_FireAbilitySound.setBuffer(m_FireAbilityBuffer);
	m_DeathSound.setBuffer(m_DeathBuffer);
	m_GameMusicSound.setBuffer(m_GameMusicBuffer);
	m_MenuMusicSound.setBuffer(m_MenuMusicBuffer);
	m_SelectTabSound.setBuffer(m_SelectTabBuffer);
	m_SlimeSound.setBuffer(m_SlimeBuffer);
	m_SpiderHissSound.setBuffer(m_SpiderHissBuffer);

	// When the player is 50 pixels away sound is full volume
	float minDistance = 150;

	// The sound reduces steadily as the player moves further away
	float attenuation = 15;

	m_FireBulletSound.setAttenuation(attenuation);
	m_FireBulletImpactSound.setAttenuation(attenuation);
	m_SlimeSound.setAttenuation(attenuation);
	m_SpiderHissSound.setAttenuation(attenuation);

	m_FireBulletSound.setMinDistance(minDistance);
	m_FireBulletImpactSound.setMinDistance(minDistance);
	m_SlimeSound.setMinDistance(minDistance);
	m_SpiderHissSound.setMinDistance(minDistance);

	m_MenuMusicSound.setLoop(true);
	m_GameMusicSound.setLoop(true);
	m_SlimeSound.setLoop(true);
}

void SoundManager::playFireBullet(Vector2f emitterLocation)
{

}

void SoundManager::playFireBulletImpact(Vector2f emitterLocation)
{

}

void SoundManager::playFireAbility()
{

}

void SoundManager::playGameMusic()
{

}

void SoundManager::playMenuMusic()
{

}

void SoundManager::playSelectTab()
{

}

void SoundManager::playSlimeSound(Vector2f emitterLocation)
{

}

void SoundManager::playSpiderHiss(Vector2f emitterLocation)
{

}

void SoundManager::update(Vector2f listenerLocation)
{

}