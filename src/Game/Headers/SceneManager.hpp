#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

#include "Scenes.hpp"

enum Scene {
	MENU,
	PLAYING,
	PAUSED,
	GAME_OVER
};

void playScene(RenderWindow& window, Scene scene);
void MenuScene(RenderWindow& window);
void PlayingScene(RenderWindow& window);

//void PausedScene();
//void GameOverScene();

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