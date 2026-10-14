#include <SFML/Graphics.hpp>

#include <optional>
#include <queue>

#include "../src/Game/Headers/GameManager.hpp"
#include "../src/Game/Headers/Scenes.hpp"

static const double DEFAULT_HOVER_ANIMATION_DURATION = 0.4;
static const double DEFAULT_IDLE_ANIMATION_DURATION = 0.4;
static const double DEFAULT_CLICKED_ANIMATION_DURATION = 0.15;

void menuScene
(
	sf::RenderWindow& window,
	sf::Font& font
)
{
	static NacreCoordinator& nc = NacreCoordinator::getInstance();

	// game state variables
	sf::Clock clock;
	std::queue<Entity> renderQueue;

	Component::Singleton::TexturesContainer loadedTextures{};

	// entity instantiation
	Entity playButton = Maker::button
	(
		Enum::Texture::TEXTURE_PLACEHOLDER,
		sf::Vector2f(
			window.getDefaultView().getSize().x / 2.0,
			window.getDefaultView().getSize().y / 2.0
		),
		{
			200.0,
			100.0
		},
		Scene::PLAYING,
		"Play",
		font,
		sf::Color::Red,
		DEFAULT_HOVER_ANIMATION_DURATION,
		DEFAULT_IDLE_ANIMATION_DURATION,
		DEFAULT_CLICKED_ANIMATION_DURATION
	);

	// onstart systems
	Start::setText(font); // font system is limited to one font
	Start::setTextOrigin();

	Start::loadTextures(loadedTextures);
	Start::loadSprites(loadedTextures);
	Start::setSpriteOrigin();
	Start::setColor();

	while (window.isOpen())
	{
		DeltaTime dt = clock.restart().asSeconds();

		auto& pixelPos = sf::Mouse::getPosition(window);
		auto& worldPos = window.mapPixelToCoords(pixelPos);

		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}

			if (const auto& mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
			{
				if (mousePressed->button == sf::Mouse::Button::Left)
				{
					nc.call<Event::MouseClick>
						(
							Event::MouseClick
							{
								{
									worldPos.x,
									worldPos.y
								}
							}
						);
				}
			} else if (event->is<sf::Event::MouseMovedRaw>() ||
				event->is<sf::Event::MouseLeft>() ||
				event->is<sf::Event::MouseEntered>())
			{
				nc.call<Event::MouseMoved>
					(
						Event::MouseMoved
						{
							{
								worldPos.x,
								worldPos.y
							}
						}
					);
			}
		}

		// update systems
		Update::doButtonTimer(dt);
		Update::applyButtonHoverAnimation();
		Update::applyButtonIdleAnimation();
		Update::applyButtonClickedAnimation();
		Update::enableButtonNextScene(window, font);

		window.clear();
		// render systems
		Render::doZIndex(renderQueue);
		Render::render(window, renderQueue);
		window.display();
	}
}