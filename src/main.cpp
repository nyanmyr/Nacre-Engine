#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

enum class GameState
{
	MENU,
	PLAYING,
	GAME_OVER
};

int main()
{
#pragma region screen stuff
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML Basics");
	window.setFramerateLimit(60);
#pragma endregion

#pragma region player circle
	float radius = 50.0f;

	sf::CircleShape circle(radius);
	circle.setFillColor(sf::Color::Green);

	circle.setOrigin(radius, radius);
	circle.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
#pragma endregion

	float speed = 5.0f;

#pragma region other circle
	sf::CircleShape other(radius);
	other.setFillColor(sf::Color::Red);

	other.setOrigin(radius, radius);
	other.setPosition(SCREEN_WIDTH - (radius * 2), SCREEN_HEIGHT - (radius * 2));
#pragma endregion

#pragma region adding a sprite
	sf::Texture texture;
	std::string path = RESOURCES_PATH "character.png";
	if (!texture.loadFromFile(path)) {
		throw std::runtime_error("File not found.");
	}


	sf::Sprite sprite;
	sprite.setTexture(texture);

	sprite.setTextureRect(sf::IntRect(0, 0, 50, 100));
	sprite.setOrigin(25, 50);
	sprite.setScale(2.0f, 2.0f);

	sprite.setPosition(100, 100);
#pragma endregion

#pragma region time
	int frame = 0;
	sf::Clock clock;
#pragma endregion

	static GameState state = GameState::MENU;

#pragma region button
	sf::RectangleShape button(sf::Vector2f(200, 50));
	button.setOrigin(200 / 2, 50 / 2);
	button.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	button.setFillColor(sf::Color::Red);

	sf::Font font;
	if (!font.loadFromFile(RESOURCES_PATH "arial.ttf")) {
	}

	sf::Text buttonText("Play", font, 24);
	buttonText.setOrigin(200 / 2, 50 / 2);
	buttonText.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	buttonText.setFillColor(sf::Color::White);
#pragma endregion

	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile(RESOURCES_PATH "Cut.wav"))
	{
	}

	sf::Sound cut;
	cut.setBuffer(buffer);

	sf::Music music;
	if (!music.openFromFile(RESOURCES_PATH "Space Jazz.ogg"))
	{
	}

	music.setLoop(true);
	music.play();

	while (window.isOpen())
	{
#pragma region get circle positions
		sf::Vector2f pos = circle.getPosition();
		sf::Vector2f otherPos = other.getPosition();
#pragma endregion

#pragma region events handling
		sf::Event event;
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed ||
				event.type == sf::Event::KeyPressed &&
				event.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}

			if (event.type == sf::Event::KeyPressed &&
				event.key.code == sf::Keyboard::Space)
			{
				state = state == GameState::MENU ? GameState::PLAYING : GameState::MENU;

				if (state == GameState::MENU)
				{
					music.setVolume(50.0f);
				}
				else
				{
					music.setVolume(100.0f);
				}

			}

			if (event.type == sf::Event::MouseButtonPressed &&
				event.mouseButton.button == sf::Mouse::Left)
			{
				if (state == GameState::MENU)
				{
					if (button.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						state = GameState::PLAYING;
					}
				}

				if (state == GameState::PLAYING)
				{
					if (((event.mouseButton.x > otherPos.x - radius) && (event.mouseButton.x < otherPos.x + radius)) &&
						((event.mouseButton.y > otherPos.y - radius) && (event.mouseButton.y < otherPos.y + radius)))
					{
						sf::Color otherColor = other.getFillColor() == sf::Color::Blue ? sf::Color::Red : sf::Color::Blue;
						other.setFillColor(otherColor);
						cut.play();
					}
				}
			}
		}
#pragma endregion

#pragma region drawing state
		window.clear(sf::Color::Black);
		{
			if (state == GameState::PLAYING)
			{
#pragma region input state
				if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
					sf::Keyboard::isKeyPressed(sf::Keyboard::A)) &&
					pos.x - radius > 0)
				{
					circle.move(-speed, 0);
				}
				if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
					sf::Keyboard::isKeyPressed(sf::Keyboard::D)) &&
					pos.x + radius < window.getSize().x)
				{
					circle.move(speed, 0);
				}
				if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
					sf::Keyboard::isKeyPressed(sf::Keyboard::W)) &&
					pos.y - radius > 0)
				{
					circle.move(0, -speed);
				}
				if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
					sf::Keyboard::isKeyPressed(sf::Keyboard::S)) &&
					pos.y + radius < window.getSize().y)
				{
					circle.move(0, speed);
				}
#pragma endregion

				if (clock.getElapsedTime().asMilliseconds() > 1)
				{
					frame = (frame + 1) % 3;
					sprite.setTextureRect(sf::IntRect(frame * 50, 0, 50, 100));
					sprite.setRotation(frame * (360.0f / 3));
					clock.restart();
				}

				window.draw(sprite);
				window.draw(other);

				float distance = std::sqrt(std::pow((pos.x - otherPos.x), 2) + std::pow((pos.y - otherPos.y), 2));
				if (distance < radius * 2)
				{
					circle.setFillColor(sf::Color::Yellow);
				}
				else
				{
					circle.setFillColor(sf::Color::Green);
				}

				window.draw(circle);
			}

			if (state == GameState::MENU) {
				window.draw(button);
				window.draw(buttonText);
			}
		}
		window.display();
#pragma endregion
	}

	return 0;
}