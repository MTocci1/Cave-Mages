#include "Engine.h"
Engine::Engine()
{
	// Get the screen resolution 
	// and create an SFML window and View
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
	m_Window.create(VideoMode(resolution.x, resolution.y),
		"Cave Mages",
		Style::Fullscreen);

	// Initialize the full screen view
	m_MainView.setSize(resolution);

	m_HudView.reset(FloatRect(0, 0, resolution.x, resolution.y));

	textureCrosshair = TextureHolder::GetTexture(
		"graphics/crosshair.png");
	spriteCrosshair.setTexture(textureCrosshair);
	spriteCrosshair.setOrigin(25, 25);

	m_WaveNumber = 1;
	m_StartNumberEnemies = 20;
	m_EnemiesLeft = 0;
	m_NewWaveRequired = true;

	arena.width = 5000;
	arena.height = 2500;
	arena.left = 0;
	arena.top = 0;

	m_fireMage.spawn(arena, resolution, TILE_SIZE);

	// Load the texture for our background vertex array
	textureBackground = TextureHolder::GetTexture(
		"graphics/ground-tile.png");

	createBackground(background, arena);
}

void Engine::run()
{
	// Timing     
	Clock clock;

	while (m_Window.isOpen())
	{
		Time dt = clock.restart();

		// Update the total game time
		m_GameTimeTotal += dt;

		// Make a decimal fraction from the delta time
		float dtAsSeconds = dt.asSeconds();

		// Call each part of the game loop in turn
		input();

		update(dtAsSeconds);

		draw();
	}
}