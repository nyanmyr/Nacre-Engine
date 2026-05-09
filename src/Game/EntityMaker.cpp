#include <SFML/Graphics.hpp>
#include "../Engine/NacreCoordinator.hpp"
#include "Headers/EntityMaker.hpp"
#include "Headers/Components.hpp"

NacreCoordinator& entityMakerNC = NacreCoordinator::getInstance();

Entity& makeCube(sf::Color col)
{
	Entity entity = entityMakerNC.createEntity();

	entityMakerNC.addComponent
	(
		entity,
		CPosition{ 0.f, 0.f }
	);

	sf::RectangleShape rect(sf::Vector2f(100.f, 100.f));

	rect.setFillColor(col);

	entityMakerNC.addComponent
	(
		entity,
		CShape{
			rect
		}
	);

	return entity;
}

Entity& makeButton(float posX, float posY, float width, float height, Scene scene, std::string str, sf::Font& font)
{
	Entity entity = entityMakerNC.createEntity();

	entityMakerNC.addComponent(
		entity,
		CPosition
		{
			posX,
			posY
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		CTransform
		{
			width,
			height
		}
	);
	sf::RectangleShape rect(sf::Vector2f(width, height));
	entityMakerNC.addComponent
	(
		entity,
		CShape
		{
			rect
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		COrigin
		{
			width / 2.f,
			height / 2.f
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		CButton
		{
			0.125f,
			true
		}
	);

	sf::Text text(font);
	entityMakerNC.addComponent
	(
		entity,
		CText
		{
			text,
			str,
			64,
			sf::Color::White,
			TextFormat::MIDDLE
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		CNextScene
		{
			scene,
			false
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		CZIndex
		{
			1,
			true
		}
	);

	return entity;
}