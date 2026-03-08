#include <iostream>

#include "Headers/GameManager.hpp"

using sf::VideoMode;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const int MAX_FPS = 60;

void Game() {
	RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Nacre Engine", sf::Style::Close);
	window.setFramerateLimit(MAX_FPS);

	// components registration
	cm.registerComponent<CPosition>();
	cm.registerComponent<CShape>();

	playScene(window, Scene::MENU);
}