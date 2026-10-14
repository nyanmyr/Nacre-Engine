#include <SFML/Graphics.hpp>

#include <stdexcept>
#include <string>

#include "Headers/GameManager.hpp"
#include "Headers/Scenes.hpp"

void main()
{
	sf::RenderWindow window
	(
		sf::VideoMode
		({ 
			Config::SCREEN_WIDTH,
			Config::SCREEN_HEIGHT 
		}),
		Config::WINDOW_NAME,
		sf::Style::Close
	);
	window.setFramerateLimit(Config::MAX_FPS);

	// resets the centerpoint of the window camera to (0,0)
	window.setView
	(
		sf::View
		(
			sf::Vector2f
			(
				0.f,
				0.f
			),
			sf::Vector2f
			(
				Config::SCREEN_WIDTH,
				Config::SCREEN_HEIGHT
			)
		)
	);

	// components registration
	nc().registerComponent<Component::Position>();
	nc().registerComponent<Component::Transform>();
	nc().registerComponent<Component::Origin>();
	nc().registerComponent<Component::Button>();
	nc().registerComponent<Component::Text>();
	nc().registerComponent<Component::NextScene>();
	nc().registerComponent<Component::ZIndex>();
	nc().registerComponent<Component::Velocity>();
	nc().registerComponent<Component::Speed>();
	nc().registerComponent<Component::PlayerController>();
	nc().registerComponent<Component::Drag>();
	nc().registerComponent<Component::Sprite>();
	nc().registerComponent<Component::Texture>();
	nc().registerComponent<Component::Color>();

	sf::Font font;
	if (!font.openFromFile(Config::FONT_FILEPATH))
	{
		throw std::runtime_error("Font not found.");
	}

	// event registration
	nc().registerEvent<Event::SetSpriteOrigin>();
	nc().registerEvent<Event::SetColor>();
	nc().registerEvent<Event::LoadSprite>();
	nc().registerEvent<Event::SetTextString>();
	nc().registerEvent<Event::SetTextSize>();
	nc().registerEvent<Event::SetTextColor>();
	nc().registerEvent<Event::MouseClick>();
	nc().registerEvent<Event::MouseMoved>();
	nc().registerEvent<Event::PlayScene>();

	// listener to event linking
	nc().listen<Event::SetSpriteOrigin>(Listener::setSpriteOrigin);
	nc().listen<Event::SetColor>(Listener::setColor);
	nc().listen<Event::LoadSprite>(Listener::loadSprite);
	nc().listen<Event::SetTextString>(Listener::setTextString);
	nc().listen<Event::SetTextSize>(Listener::setTextSize);
	nc().listen<Event::SetTextColor>(Listener::setTextColor);
	nc().listen<Event::MouseClick>(Listener::clickedButton);
	nc().listen<Event::MouseMoved>(Listener::hoverButton);
	nc().listen<Event::MouseMoved>(Listener::idleButton);
	nc().listen<Event::PlayScene>(Listener::playNextScene);

	playScene
	(
		window,
		Scene::MENU,
		font
	);
}