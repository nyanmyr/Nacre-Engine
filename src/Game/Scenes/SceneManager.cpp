#include "../Headers/Scenes.hpp"
#include <stdexcept>

void playScene(sf::RenderWindow& window, Scene scene, sf::Font& font) {
    switch (scene) {
    case Scene::MENU:
        menuScene(window, font);
        break;
    case Scene::PLAYING:
        playingScene(window, font);
        break;
    default:
        throw std::runtime_error("Scene does not exist.");
        break;
    }
}
