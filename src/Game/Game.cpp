#include <SFML/Graphics.hpp>

#include <stdexcept>
#include <string>

#include "Headers/GameManager.hpp"
#include "Headers/Scenes.hpp"

static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 600;
static const int MAX_FPS = 60;
static const std::string FONT_FILEPATH = RESOURCES_PATH "arial.ttf";
static const std::string WINDOW_NAME = "Nacre Engine";
static NacreCoordinator& nc = NacreCoordinator::getInstance();

void main()
{
	sf::RenderWindow window(sf::VideoMode({ SCREEN_WIDTH, SCREEN_HEIGHT }), WINDOW_NAME, sf::Style::Close);
	window.setFramerateLimit(MAX_FPS);

	// components registration
	nc.registerComponent<Component::Position>();
	nc.registerComponent<Component::Transform>();
	nc.registerComponent<Component::Origin>();
	nc.registerComponent<Component::Button>();
	nc.registerComponent<Component::Text>();
	nc.registerComponent<Component::NextScene>();
	nc.registerComponent<Component::ZIndex>();
	nc.registerComponent<Component::Velocity>();
	nc.registerComponent<Component::Speed>();
	nc.registerComponent<Component::PlayerController>();
	nc.registerComponent<Component::Drag>();
	nc.registerComponent<Component::Sprite>();
	nc.registerComponent<Component::Texture>();
	nc.registerComponent<Component::Color>();

	sf::Font font;
	if (!font.openFromFile(FONT_FILEPATH))
	{
		throw std::runtime_error("Font not found.");
	}

	// event registration
	nc.registerEvent<Event::SetSpriteOrigin>();
	nc.registerEvent<Event::SetColor>();
	nc.registerEvent<Event::LoadSprite>();
	nc.registerEvent<Event::SetTextString>();
	nc.registerEvent<Event::SetTextSize>();
	nc.registerEvent<Event::SetTextColor>();
	nc.registerEvent<Event::MouseClick>();
	nc.registerEvent<Event::MouseMoved>();

	// functions creation
	std::function<void(Event::SetSpriteOrigin)> setSpriteOrigin = Listener::setSpriteOrigin;
	std::function<void(Event::SetColor)> setColor = Listener::setColor;
	std::function<void(Event::LoadSprite)> loadSprite = Listener::loadSprite;
	std::function<void(Event::SetTextString)> setTextString = Listener::setTextString;
	std::function<void(Event::SetTextSize)> setTextSize = Listener::setTextSize;
	std::function<void(Event::SetTextColor)> setTextColor = Listener::setTextColor;
	std::function<void(Event::MouseClick)> setButtonClicked = Listener::clickedButton;
	std::function<void(Event::MouseMoved)> mouseHovered = Listener::hoverButton;
	std::function<void(Event::MouseMoved)> idleButton = Listener::idleButton;

	// listener function linking
	nc.listen<Event::SetSpriteOrigin>(setSpriteOrigin);
	nc.listen<Event::SetColor>(setColor);
	nc.listen<Event::LoadSprite>(loadSprite);
	nc.listen<Event::SetTextString>(setTextString);
	nc.listen<Event::SetTextSize>(setTextSize);
	nc.listen<Event::SetTextColor>(setTextColor);
	nc.listen<Event::MouseClick>(setButtonClicked);
	nc.listen<Event::MouseMoved>(mouseHovered);
	nc.listen<Event::MouseMoved>(idleButton);

	playScene
	(
		window,
		Scene::MENU,
		font
	);
}