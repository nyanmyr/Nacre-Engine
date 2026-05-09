#include <SFML/Graphics.hpp>
#include "../Engine/NacreCoordinator.hpp"
#include "Headers/EntityMaker.hpp"
#include "Headers/Components.hpp"

NacreCoordinator& entityMakerNC = NacreCoordinator::getInstance();

Entity& makePlayer(float posX, float posY, float width, float height, float maxVelocityX, float maxVelocityY, float speedX, float speedY)
{
	Entity entity = entityMakerNC.createEntity();

	entityMakerNC.addComponent
	(
		entity,
		CPosition
		{ 
			posX,
			posY
		}
	);

	sf::RectangleShape rect(sf::Vector2f(width, height));
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
			width / 2.f,
			height / 2.f
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		CVelocity
		{
			maxVelocityX,
			maxVelocityY
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		CSpeed
		{
			speedX,
			speedY
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