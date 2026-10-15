#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <SFML/Graphics.hpp>

#include <stdexcept>
#include <string>

namespace Config
{
	inline constexpr int SCREEN_WIDTH = 800;
	inline constexpr int SCREEN_HEIGHT = 600;
	inline constexpr int MAX_FPS = 60;
	inline const std::string FONT_FILEPATH = RESOURCES_PATH "arial.ttf";
	inline const std::string WINDOW_NAME = "Nacre Engine";

	inline sf::Font& font()
	{
		static sf::Font font =
			[] {
			sf::Font f;
			if (!f.openFromFile(Config::FONT_FILEPATH))
			{
				throw std::runtime_error("Font not found: " + std::string(Config::FONT_FILEPATH));
			}
			return f;
			}();

		return font;
	}

	inline sf::RenderWindow& window()
	{
		static sf::RenderWindow window =
			[] {
			sf::RenderWindow w
			(
				sf::VideoMode
				({
					Config::SCREEN_WIDTH,
					Config::SCREEN_HEIGHT
					}),
				Config::WINDOW_NAME,
				sf::Style::Close
			);

			w.setFramerateLimit(Config::MAX_FPS);

			// resets the centerpoint of the window camera to (0,0)
			w.setView
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

			return w;
			}();

		return window;
	}
}

#endif