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
	nc.registerComponent<Component::TexturesContainer>();
	nc.registerComponent<Component::Color>();

	sf::Font font;
	if (!font.openFromFile(FONT_FILEPATH))
	{
		throw std::runtime_error("Font not found.");
	}

	playScene
	(
		window,
		Scene::MENU,
		font
	);
}