#include <SFML/Graphics.hpp>
#include "../Engine/Nacre.hpp"
#include "Headers/EntityMaker.hpp"
#include "Headers/Components.hpp"

EntityManager& entityMakerEM = EntityManager::getInstance();
ComponentManager& entityMakerCM = ComponentManager::getInstance();

Entity& makeCube(sf::Color col)
{
	Entity entity = entityMakerEM.createEntity();

	entityMakerCM.addComponent(
		entity,
		CPosition{ 0.f, 0.f }
	);

	sf::RectangleShape rect(sf::Vector2f(100.f, 100.f));

	rect.setFillColor(col);

	entityMakerCM.addComponent(
		entity,
		CShape{
			rect
		}
	);

	return entity;
}