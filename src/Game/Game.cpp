#include <iostream>

#include "Headers/GameManager.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const int MAX_FPS = 60;

void Game() {
	RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Nacre Engine", sf::Style::Close);
	window.setFramerateLimit(MAX_FPS);

	// register components
	cm.registerComponent<CPosition>();
	cm.registerComponent<CLineSegment>();
	cm.registerComponent<CVelocity>();
	cm.registerComponent<CShape>();
	cm.registerComponent<CLifeTime>();
	cm.registerComponent<CZIndex>();

	// entity initialization

	Clock clock;
	Clock FPSClock;

	int frameCount = 0;
	int fps = 0;

	while (window.isOpen())
	{
		DeltaTime dt = clock.restart().asSeconds();

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}

		}

		frameCount++;
		if (FPSClock.getElapsedTime().asSeconds() >= 1)
		{
			fps = frameCount;
			cout << "FPS: " << fps << "\n";
			frameCount = 0;
			FPSClock.restart();
		}

		// input systems
		//PlayerInputSystem(GetPlayerID());

		// update systems
		//SpawnerSystem(dt);

		MovementSystem(dt);

		KeyboardInputSystem(window);

		HandleLifetimeSystem(dt);

		window.clear();
		// render systems
		RenderSystem(window);
		window.display();
	}

}