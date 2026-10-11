#include "Headers/Listeners.hpp"
#include "Headers/Components.hpp"

#include <stdexcept>

static NacreCoordinator& nc = NacreCoordinator::getInstance();

namespace Listener
{
	void setSpriteOrigin(Event::SetSpriteOrigin event)
	{
		if (event.target == NULL_ENTITY) throw std::runtime_error("Error: null entity");

		auto& originArray = nc.getComponentArray<Component::Origin>();
		auto& spriteArray = nc.getComponentArray<Component::Sprite>();

		if (!originArray->hasData(event.target) ||
			!spriteArray->hasData(event.target))
		{
			return;
		}

		Component::Sprite& sprite = spriteArray->getData(event.target);
		const Component::Origin& origin = originArray->getData(event.target);

		sprite.body->setOrigin
		(
			sf::Vector2f
			(
				origin.offsetX / sprite.body->getScale().x,
				origin.offsetY / sprite.body->getScale().y
			)
		);
	}
	void setColor(Event::SetColor event)
	{
		if (event.target == NULL_ENTITY) throw std::runtime_error("Error: null entity");

		auto& spriteArray = nc.getComponentArray<Component::Sprite>();

		if (!spriteArray->hasData(event.target))
		{
			return;
		}

		Component::Sprite& sprite = spriteArray->getData(event.target);

		sprite.body->setColor(event.color.data);
	}
	void loadSprite(Event::LoadSprite event)
	{
		if (event.target == NULL_ENTITY) throw std::runtime_error("Error: null entity");

		auto& transformArray = nc.getComponentArray<Component::Transform>();
		auto& textureArray = nc.getComponentArray<Component::Texture>();

		if (!transformArray->hasData(event.target) ||
			!textureArray->hasData(event.target))
		{
			return;
		}

		Component::Texture& texture = textureArray->getData(event.target);
		Component::Transform& transform = transformArray->getData(event.target);

		if (event.loadedTextures.map.find(texture.data) == event.loadedTextures.map.end())
		{
			throw std::runtime_error("Texture has not been loaded.");
		}

		event.sprite.body.emplace(event.loadedTextures.map.at(texture.data));
		event.sprite.body->setScale
		(
			sf::Vector2f
			(
				transform.width / event.sprite.body->getGlobalBounds().size.x,
				transform.height / event.sprite.body->getGlobalBounds().size.y
			)
		);
	}
}