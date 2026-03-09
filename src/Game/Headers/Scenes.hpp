#ifndef SCENES_HPP
#define SCENES_HPP

#include <SFML/Graphics.hpp>

#include <stdexcept>

using std::runtime_error;
using sf::RenderWindow;

enum Scene {
	MENU,
	PLAYING,
	PAUSED,
	GAME_OVER
};

void playScene(RenderWindow& window, Scene scene);
void MenuScene(RenderWindow& window);
void PlayingScene(RenderWindow& window);

void playScene(RenderWindow& window, Scene scene) {
	switch (scene) {
	case MENU:
		MenuScene(window);
		break;
	case PLAYING:
		PlayingScene(window);
		break;
	case PAUSED:
		break;
	case GAME_OVER:
		break;
	default:
		throw new runtime_error("Scene does not exist.");
		break;
	}
}

#endif