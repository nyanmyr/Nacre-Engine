#ifndef ENTITY_MAKER_HPP
#define ENTITY_MAKER_HPP

#include <SFML/Graphics.hpp>
#include "Scenes.hpp"

Entity& makeCube(sf::Color col);
Entity& makeButton(float posX, float posY, float width, float height, Scene scene, std::string str, sf::Font& font);

#endif