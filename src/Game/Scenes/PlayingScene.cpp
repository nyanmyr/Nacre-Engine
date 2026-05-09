#include <SFML/Graphics.hpp>
#include "../src/Game/Headers/GameManager.hpp"
#include "../src/Game/Headers/Scenes.hpp"

using sf::RenderWindow;
using sf::Clock;
using sf::Event;
using sf::Keyboard::Scancode;

void PlayingScene(sf::RenderWindow& window, sf::Font& font) {
	NacreCoordinator& nc = NacreCoordinator::getInstance();

	// game state variables
	Clock clock;
	std::queue<Entity> renderQueue;

	// entity instantiation
	Entity player = makePlayer
	(
		window.getSize().x / 2,
		window.getSize().y / 2,
		50,
		50,
		20,
		20,
		10,
		10
	);

	// onstart systems
	SetTextSystem(font); // font system is limited to one font
	SetTextOriginSystem();
	SetShapeOriginSystem();

	while (window.isOpen())
	{
		DeltaTime dt = clock.restart().asSeconds();

		while (const std::optional event = window.pollEvent())
		{
			if (event->is<Event::Closed>())
			{
				window.close();
			}

			if (const auto& buttonPress = event->getIf<sf::Event::KeyPressed>())
			{
				MovementDirection movDir = MovementDirection::NONE;

				switch (buttonPress->scancode)
				{
					case sf::Keyboard::Scancode::W:
						movDir = MovementDirection::NORTH;
						break;
					case sf::Keyboard::Scancode::A:
						movDir = MovementDirection::WEST;
						break;
					case sf::Keyboard::Scancode::S:
						movDir = MovementDirection::SOUTH;
						break;
					case sf::Keyboard::Scancode::D:
						movDir = MovementDirection::EAST;
						break;
				}

				PlayerControlSystem(player, movDir, dt);
			}
		}

		// systems
		MoveSystem();

		window.clear();
		// render systems
		ZIndexSystem(renderQueue);
		RenderSystem(window, renderQueue);
		window.display();
	}
}