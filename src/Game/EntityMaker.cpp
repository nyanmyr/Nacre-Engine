#include "Headers/EntityMaker.hpp"

#include <SFML/Graphics.hpp>
#include "../Engine/NacreCoordinator.hpp"
#include "Headers/Components.hpp"
#include "Headers/Enums.hpp"

static NacreCoordinator& nc = NacreCoordinator::getInstance();

Entity makePlayer
(
	const Enum::Texture texture,
	const sf::Vector2f pos,
	const sf::Vector2f size,
	const sf::Vector2f minVelocity,
	const sf::Vector2f maxVelocity,
	const sf::Vector2f speed,
	const sf::Vector2f drag,
	const sf::Color col
)
{
	Entity entity = nc.createEntity();

	nc.addComponent
	(
		entity,
		Component::Position
		{ 
			pos.x,
			pos.y
		}
	);
	nc.addComponent
	(
		entity,
		Component::ZIndex
		{
			1,
			true
		}
	);
	nc.addComponent
	(
		entity,
		Component::Origin
		{
			size.x / 2.0,
			size.y / 2.0
		}
	);
	nc.addComponent
	(
		entity,
		Component::Velocity
		{
			minVelocity.x,
			minVelocity.y,
			maxVelocity.x,
			maxVelocity.y
		}
	);
	nc.addComponent
	(
		entity,
		Component::Speed
		{
			speed.x,
			speed.y
		}
	);
	nc.addComponent
	(
		entity,
		Component::Drag
		{
			drag.x,
			drag.y
		}
	);
	nc.addComponent
	(
		entity,
		Component::PlayerController
		{
			true
		}
	);
	nc.addComponent
	(
		entity,
		Component::Transform
		{
			size.x,
			size.y
		}
	);
	nc.addComponent
	(
		entity,
		Component::Texture{ texture }
	);
	nc.addComponent
	(
		entity,
		Component::Sprite{}
	);

	nc.addComponent
	(
		entity,
		Component::Color{ col }
	);

	return entity;
}

Entity makeButton
(
	const Enum::Texture texture,
	const sf::Vector2f pos,
	const sf::Vector2f size,
	const Scene scene,
	const std::string str,
	const sf::Font& font,
	const sf::Color col
)
{
	Entity entity = nc.createEntity();

	nc.addComponent(
		entity,
		Component::Position
		{
			pos.x,
			pos.y
		}
	);
	nc.addComponent
	(
		entity,
		Component::Transform
		{
			size.x,
			size.y
		}
	);
	nc.addComponent
	(
		entity,
		Component::Origin
		{
			size.x / 2.0,
			size.y / 2.0
		}
	);
	nc.addComponent
	(
		entity,
		Component::Button
		{
			0.125f,
			true
		}
	);

	sf::Text text(font);
	nc.addComponent
	(
		entity,
		Component::Text
		{
			text,
			str,
			64,
			sf::Color::Black,
			Enum::TextFormat::MIDDLE
		}
	);
	nc.addComponent
	(
		entity,
		Component::NextScene
		{
			scene,
			false
		}
	);
	nc.addComponent
	(
		entity,
		Component::ZIndex
		{
			1,
			true
		}
	);
	nc.addComponent
	(
		entity,
		Component::Transform
		{
			size.x,
			size.y
		}
	);
	nc.addComponent
	(
		entity,
		Component::Texture{ texture }
	);
	nc.addComponent
	(
		entity,
		Component::Sprite{}
	);

	nc.addComponent
	(
		entity,
		Component::Color{ col }
	);

	return entity;
}

Entity makeLoadedTexturesContainer()
{
	Entity entity = nc.createEntity();

	nc.addComponent
	(
		entity,
		Component::TexturesContainer{}
	);

	return entity;
}