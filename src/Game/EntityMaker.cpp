#include <SFML/Graphics.hpp>
#include "../Engine/NacreCoordinator.hpp"
#include "Headers/EntityMaker.hpp"
#include "Headers/Components.hpp"

NacreCoordinator& entityMakerNC = NacreCoordinator::getInstance();

Entity makePlayer
(
	const sf::Vector2f pos,
	const sf::Vector2f minVelocity,
	const sf::Vector2f size,
	const sf::Vector2f maxVelocity,
	const sf::Vector2f speed,
	const sf::Vector2f drag
)
{
	Entity entity = entityMakerNC.createEntity();

	entityMakerNC.addComponent
	(
		entity,
		CPosition
		{ 
			pos.x,
			pos.y
		}
	);

	sf::RectangleShape rect(sf::Vector2f(size.x, size.y));
	rect.setFillColor(sf::Color::Green);

	entityMakerNC.addComponent
	(
		entity,
		CShape{
			rect
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
	entityMakerNC.addComponent
	(
		entity,
		COrigin
		{
			size.x / 2.f,
			size.y / 2.f
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		CVelocity
		{
			minVelocity.x,
			minVelocity.y,
			maxVelocity.x,
			maxVelocity.y
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		CSpeed
		{
			speed.x,
			speed.y
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		CDrag
		{
			drag.x,
			drag.y
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		CPlayerController
		{
			true
		}
	);

	return entity;
}

Entity makeButton
(
	const sf::Vector2f pos,
	const sf::Vector2f size,
	const Scene scene,
	const std::string str,
	const sf::Font& font
)
{
	Entity entity = entityMakerNC.createEntity();

	entityMakerNC.addComponent(
		entity,
		CPosition
		{
			pos.x,
			pos.y
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		CTransform
		{
			size.x,
			size.y
		}
	);
	sf::RectangleShape rect(sf::Vector2f(size.x, size.y));
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
			size.x / 2.f,
			size.y / 2.f
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
			sf::Color::Black,
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