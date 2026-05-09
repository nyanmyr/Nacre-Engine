#include "../Headers/Scenes.hpp"
#include <stdexcept>

void playScene(sf::RenderWindow& window, Scene scene, sf::Font& font) {
    switch (scene) {
    case MENU:
        MenuScene(window, font);
        break;
    case PLAYING:
        PlayingScene(window, font);
        break;
    case PAUSED:
        break;
    case GAME_OVER:
        break;
    default:
        throw std::runtime_error("Scene does not exist.");
        break;
    }
}
