#ifndef MENU_SCENE_HPP
#define MENU_SCENE_HPP

#include <SFML/Graphics.hpp>

using sf::Vector2f;
using sf::Clock;
using sf::Event;
using sf::Keyboard;

using DeltaTime = float;

void MenuScene(RenderWindow& window) {

	// entity instantiation
	Entity player = em.createEntity();
	cm.addComponent(
		player,
		CPosition{
		((float)window.getSize().x / 2) - 50, ((float)window.getSize().y / 2) - 50
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

			if (event.type == Event::KeyReleased)
			{
				if (event.key.code == Keyboard::Space)
				{
					// on exit
					cm.entityDestroyed(player);
					em.destroyEntity(player);

					playScene(window, PLAYING);
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

#endif