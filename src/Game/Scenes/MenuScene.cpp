#include <SFML/Graphics.hpp>
#include "../src/Game/Headers/GameManager.hpp"
#include "../src/Game/Headers/Scenes.hpp"

using sf::RenderWindow;
using sf::Clock;
using sf::Event;
using sf::Keyboard::Scancode;

void MenuScene(sf::RenderWindow& window, sf::Font& font) {
	NacreCoordinator& nc = NacreCoordinator::getInstance();

	// entity instantiation
	Entity player = makeCube(sf::Color::Red);

	Clock clock;
	std::queue<Entity> renderQueue;
	
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

			//if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			//{
			//	if (keyPressed->scancode == sf::Keyboard::Scancode::Space)
			//	{
			//	}
			//}
		}

		// update systems
		//ButtonClickedSystem(sf::Vector2i(worldPos.x, worldPos.y), buttonClicked, dt);
		//NextSceneSystem(window, font);

		window.clear();
		// render systems
		ZIndexSystem(renderQueue);
		RenderSystem(window, renderQueue);
		window.display();
	}
}