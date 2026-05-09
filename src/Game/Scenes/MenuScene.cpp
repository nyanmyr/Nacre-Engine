#include <SFML/Graphics.hpp>
#include "../src/Game/Headers/GameManager.hpp"
#include "../src/Game/Headers/Scenes.hpp"

using sf::RenderWindow;
using sf::Clock;
using sf::Event;
using sf::Keyboard::Scancode;

void MenuScene(sf::RenderWindow& window, sf::Font& font) {
	NacreCoordinator& nc = NacreCoordinator::getInstance();

	// game state variables
	Clock clock;
	std::queue<Entity> renderQueue;
	bool buttonClicked = false;

	// entity instantiation
	Entity playButton = makeButton
	(
		window.getSize().x / 2,
		window.getSize().y / 2,
		200,
		100,
		Scene::PLAYING,
		"Play",
		font
	);

	// onstart systems
	SetTextSystem(font); // font system is limited to one font
	SetTextOriginSystem();
	SetShapeOriginSystem();

	while (window.isOpen())
	{
		DeltaTime dt = clock.restart().asSeconds();

		auto& pixelPos = sf::Mouse::getPosition(window);
		auto& worldPos = window.mapPixelToCoords(pixelPos);

		while (const std::optional event = window.pollEvent())
		{
			if (event->is<Event::Closed>())
			{
				window.close();
			}

			if (const auto& mousePress = event->getIf<sf::Event::MouseButtonPressed>())
			{
				buttonClicked = true;
			}
		}

		// update systems
		ButtonClickedSystem(sf::Vector2i(worldPos.x, worldPos.y), buttonClicked, dt);
		NextSceneSystem(window, font);

		window.clear();
		// render systems
		ZIndexSystem(renderQueue);
		RenderSystem(window, renderQueue);
		window.display();
	}
}