#ifndef ENTITY_MAKER_HPP
#define ENTITY_MAKER_HPP

#include <SFML/Graphics.hpp>
#include "Scenes.hpp"

// could prolly use some Vector2fs
Entity& makePlayer(float posX, float posY, float width, float height, float maxVelocityX, float maxVelocityY, float speedX, float speedY);
Entity& makeButton(float posX, float posY, float width, float height, Scene scene, std::string str, sf::Font& font);

#endif