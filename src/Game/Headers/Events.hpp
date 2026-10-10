#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <SFML/Graphics.hpp>
#include "../src/Engine/NacreCoordinator.hpp"
#include "Components.hpp"

namespace Event
{
	struct SetSpriteOrigin
	{
		Entity target = NULL_ENTITY;
	};
	struct SetColor
	{
		Entity target = NULL_ENTITY;
	};
	struct LoadSprite
	{
		Entity target = NULL_ENTITY;
		Component::Sprite& sprite;
		const Component::Singleton::TexturesContainer& loadedTextures;
	};
}

#endif