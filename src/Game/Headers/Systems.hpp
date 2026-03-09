#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP

#include <SFML/Graphics.hpp>

using sf::RenderWindow;

void RenderSystem(RenderWindow& window);

EntityManager& em = EntityManager::getInstance();
ComponentManager& cm = ComponentManager::getInstance();

void RenderSystem(RenderWindow& window)
{
	auto& shapes = cm.getComponentArray<CShape>();
	auto& positions = cm.getComponentArray<CPosition>();

	for (auto& [entity, shape] : shapes->getAll())
	{
		if (positions->hasData(entity))
		{
			CPosition pos = positions->getData(entity);
			shape.rect.setPosition(pos.x, pos.y);
			window.draw(shape.rect);
		}
	}
}

#endif
