#include "../Engine/Nacre.hpp"
#include "Headers/EntityMaker.hpp"
#include "Headers/Components.hpp"

EntityManager& entityMakerEM = EntityManager::getInstance();
ComponentManager& entityMakerCM = ComponentManager::getInstance();

Entity& makeCube()
{
	Entity entity = entityMakerEM.createEntity();

	entityMakerCM.addComponent(
		entity,
		CPosition{ 0.f, 0.f }
	);
	entityMakerCM.addComponent(
		entity,
		CShape{
		sf::RectangleShape(sf::Vector2f(100.f, 100.f))
		}
	);

	return entity;
}