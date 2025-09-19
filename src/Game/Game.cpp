#include <iostream>

#include "Headers/GameManager.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const int MAX_FPS = 60;

void Game() {
	RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Nacre Engine", sf::Style::Close);
	window.setFramerateLimit(MAX_FPS);

	// components registration
	cm.registerComponent<CPosition>();
	cm.registerComponent<CShape>();

	// entity instantiation
	Entity player = em.createEntity();
	cm.addComponent(
		player,
		CPosition{
		(SCREEN_WIDTH / 2) - 50, (SCREEN_HEIGHT / 2) - 50
		}
	);
	cm.addComponent(
		player,
		CShape{
		RectangleShape(Vector2f(100.f, 100.f))
		}
	);

	Clock clock;

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

		// systems

		window.clear();
		// render systems
		RenderSystem(window);
		window.display();
	}

}