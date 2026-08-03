#ifndef ENTITY_MAKER_HPP
#define ENTITY_MAKER_HPP

#include <SFML/Graphics.hpp>
#include "Scenes.hpp"

Entity makePlayer
(
	const sf::Vector2f pos,
	const sf::Vector2f size,
	const sf::Vector2f minVelocity,
	const sf::Vector2f maxVelocity,
	const sf::Vector2f speed,
	const sf::Vector2f drag
);
Entity makeButton
(
	const sf::Vector2f pos,
	const sf::Vector2f size,
	const Scene scene,
	const std::string str,
	const sf::Font& font
);

#endif