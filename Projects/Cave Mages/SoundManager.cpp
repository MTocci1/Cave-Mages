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
	m_MenuMusicBuffer.loadFromFile("sound/menu-music.wav");
	m_SelectTabBuffer.loadFromFile("sound/select-tab.mp3");
	m_DashBuffer.loadFromFile("sound/dash.wav");
	m_CraftBuffer.loadFromFile("sound/craft.wav");

	m_FireBulletSound.setBuffer(m_FireBulletBuffer);
	m_FireBulletImpactSound.setBuffer(m_FireBulletImpactBuffer);
	m_FireAbilitySound.setBuffer(m_FireAbilityBuffer);
	m_DeathSound.setBuffer(m_DeathBuffer);
	m_GameMusicSound.setBuffer(m_GameMusicBuffer);
	m_MenuMusicSound.setBuffer(m_MenuMusicBuffer);
	m_SelectTabSound.setBuffer(m_SelectTabBuffer);
	m_DashSound.setBuffer(m_DashBuffer);
	m_CraftSound.setBuffer(m_CraftBuffer);
	
	m_MenuMusicSound.setLoop(true);
	m_GameMusicSound.setLoop(true);

	m_GameMusicSound.setVolume(3);
	m_FireAbilitySound.setVolume(30);
	m_FireBulletSound.setVolume(8);
	m_FireBulletImpactSound.setVolume(3);
	m_SelectTabSound.setVolume(15);
	m_DashSound.setVolume(15);
	m_CraftSound.setVolume(15);
}

void SoundManager::playFireBullet()
{
	if (m_FireBulletSound.getStatus() == Sound::Status::Stopped) {
		m_FireBulletSound.setRelativeToListener(true);
		m_FireBulletSound.play();
	}
	if (m_FireBulletSound.getStatus() == Sound::Status::Playing) {
		m_FireBulletSound.stop();
		m_FireBulletSound.play();
	}
}

void SoundManager::playFireBulletImpact()
{
	if (m_FireBulletImpactSound.getStatus() == Sound::Status::Stopped) {
		m_FireBulletImpactSound.setRelativeToListener(true);
		m_FireBulletImpactSound.play();
	}
	if (m_FireBulletImpactSound.getStatus() == Sound::Status::Playing) {
		m_FireBulletImpactSound.stop();
		m_FireBulletImpactSound.play();
	}
}

void SoundManager::playFireAbility()
{
	if (m_FireAbilitySound.getStatus() == Sound::Status::Stopped) {
		m_FireAbilitySound.setRelativeToListener(true);
		m_FireAbilitySound.play();
	}
}

void SoundManager::stopFireAbility()
{
	if (m_FireAbilitySound.getStatus() == Sound::Status::Playing) {
		m_FireAbilitySound.stop();
	}
}

void SoundManager::playGameMusic()
{
	if (m_GameMusicSound.getStatus() == Sound::Status::Stopped) {
		m_GameMusicSound.setRelativeToListener(true);
		m_GameMusicSound.play();
	}
}

void SoundManager::stopGameMusic()
{
	if (m_GameMusicSound.getStatus() == Sound::Status::Playing) {
		m_GameMusicSound.stop();
	}
}

void SoundManager::playMenuMusic()
{
	if (m_MenuMusicSound.getStatus() == Sound::Status::Stopped) {
		m_GameMusicSound.setRelativeToListener(true);
		m_MenuMusicSound.play();
	}
}

void SoundManager::stopMenuMusic()
{
	if (m_MenuMusicSound.getStatus() == Sound::Status::Playing) {
		m_MenuMusicSound.stop();
	}
}

void SoundManager::playSelectTab()
{
	if (m_SelectTabSound.getStatus() == Sound::Status::Stopped) {
		m_SelectTabSound.setRelativeToListener(true);
		m_SelectTabSound.play();
	}
	if (m_SelectTabSound.getStatus() == Sound::Status::Playing) {
		m_SelectTabSound.stop();
		m_SelectTabSound.play();
	}
}

void SoundManager::playDashSound()
{
	if (m_DashSound.getStatus() == Sound::Status::Stopped) {
		m_DashSound.setRelativeToListener(true);
		m_DashSound.play();
	}
	if (m_DashSound.getStatus() == Sound::Status::Playing) {
		m_DashSound.stop();
		m_DashSound.play();
	}
}

void SoundManager::playCraftSound()
{
	if (m_CraftSound.getStatus() == Sound::Status::Stopped) {
		m_CraftSound.setRelativeToListener(true);
		m_CraftSound.play();
	}
	if (m_CraftSound.getStatus() == Sound::Status::Playing) {
		m_CraftSound.stop();
		m_CraftSound.play();
	}
}

void SoundManager::playDeathSound()
{
	m_DeathSound.play();
}

void SoundManager::update(Vector2f listenerLocation)
{
	// Set the listener location
	m_ListenerLocation = listenerLocation;
	Listener::setPosition(m_ListenerLocation.x,
		m_ListenerLocation.y, 0.0f);
	Listener::setDirection(0.0f, -1.0f, 0.0f);
}