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

		auto& colorArray = nc.getComponentArray<Component::Color>();
		auto& spriteArray = nc.getComponentArray<Component::Sprite>();

		if (!colorArray->hasData(event.target) ||
			!spriteArray->hasData(event.target))
		{
			return;
		}

		Component::Sprite& sprite = spriteArray->getData(event.target);
		const Component::Color& color = colorArray->getData(event.target);

		sprite.body->setColor(color.col);
	}
}