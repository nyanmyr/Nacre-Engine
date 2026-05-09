#include <SFML/Graphics.hpp>
#include "../src/Game/Headers/GameManager.hpp"
#include "../src/Game/Headers/Scenes.hpp"

using sf::RenderWindow;
using sf::Clock;
using sf::Event;
using sf::Keyboard::Scancode;

void PlayingScene(sf::RenderWindow& window, sf::Font& font) {
	NacreCoordinator& nc = NacreCoordinator::getInstance();

	// entity instantiation
	Entity player = makeCube(sf::Color::Green);

	Clock clock;

	while (window.isOpen())
	{
		DeltaTime dt = clock.restart().asSeconds();

		while (const std::optional event = window.pollEvent())
		{
			if (event->is<Event::Closed>())
			{
				window.close();
			}
		}

		// systems

		window.clear();
		// render systems
		window.display();
	}
}