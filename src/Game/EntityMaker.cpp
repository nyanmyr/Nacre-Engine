#include <SFML/Graphics.hpp>
#include "../Engine/Nacre.hpp"
#include "Headers/EntityMaker.hpp"
#include "Headers/Components.hpp"

NacreManager& entityMakerNM = NacreManager::getInstance();

Entity& makeCube(sf::Color col)
{
	Entity entity = entityMakerNM.createEntity();

	entityMakerNM.addComponent
	(
		entity,
		CPosition{ 0.f, 0.f }
	);

	sf::RectangleShape rect(sf::Vector2f(100.f, 100.f));

	rect.setFillColor(col);

	entityMakerNM.addComponent
	(
		entity,
		CShape{
			rect
		}
	);

	return entity;
}