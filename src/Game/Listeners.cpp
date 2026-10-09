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

		Component::Origin& origin = originArray->getData(event.target);
		Component::Sprite& sprite = spriteArray->getData(event.target);

		sprite.body->setOrigin
		(
			sf::Vector2f
			(
				origin.offsetX / sprite.body->getScale().x,
				origin.offsetY / sprite.body->getScale().y
			)
		);
	}
}