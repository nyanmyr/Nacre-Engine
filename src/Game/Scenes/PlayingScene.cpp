#include <SFML/Graphics.hpp>
#include "../src/Game/Headers/GameManager.hpp"
#include "../src/Game/Headers/Scenes.hpp"

using sf::RenderWindow;
using sf::Clock;
using sf::Event;
using sf::Keyboard::Scancode;

void PlayingScene(RenderWindow& window) {
	NacreManager& nm = NacreManager::getInstance();

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

			if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				if (keyPressed->scancode == sf::Keyboard::Scancode::Space)
				{
					// on exit
					nm.deleteEntity(player);

					playScene(window, MENU);
					window.close();
				}
			}
		}

		// systems

		window.clear();
		// render systems
		RenderSystem(window);
		window.display();
	}
}