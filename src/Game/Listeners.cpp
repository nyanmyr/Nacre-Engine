#include "Headers/Listeners.hpp"
#include "Headers/Components.hpp"
#include "Headers/Scenes.hpp"

#include <stdexcept>

static bool checkCollision
(
	sf::Vector2f a,
	sf::Vector2f b,
	sf::Vector2f aTrans,
	sf::Vector2f bTrans
)
{
	// AABB collision
	if (a.x + (aTrans.x / 2.f) > b.x - (bTrans.x / 2.f) &&
		a.x - (aTrans.x / 2.f) < b.x + (bTrans.x / 2.f) &&
		a.y + (aTrans.y / 2.f) > b.y - (bTrans.y / 2.f) &&
		a.y - (aTrans.y / 2.f) < b.y + (bTrans.y / 2.f))
	{
		return true;
	}

	return false;
}

namespace Listener
{
	void setSpriteOrigin(Event::SetSpriteOrigin event)
	{
		if (event.target == NULL_ENTITY) throw std::runtime_error("Error: null entity");

		auto& spriteArray = nc().getComponentArray<Component::Sprite>();
		auto& transformArray = nc().getComponentArray<Component::Transform>();

		if (!spriteArray->hasData(event.target) ||
			!transformArray->hasData(event.target))
		{
			return;
		}

		auto& sprite = spriteArray->getData(event.target);
		const auto& transform = transformArray->getData(event.target);

		switch (event.originPoint.data)
		{
		case Enum::OriginPoint::LEFT:
			event.originOffsets.x = 0.0;
			event.originOffsets.y = transform.height / 2.0;
			break;
		case Enum::OriginPoint::RIGHT:
			event.originOffsets.x = transform.width;
			event.originOffsets.y = transform.height / 2.0;
			break;
		case Enum::OriginPoint::TOP:
			event.originOffsets.x = transform.width / 2.0;
			event.originOffsets.y = 0.0;
			break;
		case Enum::OriginPoint::BOTTOM:
			event.originOffsets.x = transform.width / 2.0;
			event.originOffsets.y = transform.height;
			break;
		case Enum::OriginPoint::TOP_LEFT:
			event.originOffsets.x = 0.0;
			event.originOffsets.y = 0.0;
			break;
		case Enum::OriginPoint::TOP_RIGHT:
			event.originOffsets.x = transform.width;
			event.originOffsets.y = 0.0;
			break;
		case Enum::OriginPoint::BOTTOM_LEFT:
			event.originOffsets.x = 0.0;
			event.originOffsets.y = transform.height;
			break;
		case Enum::OriginPoint::BOTTOM_RIGHT:
			event.originOffsets.x = transform.width;
			event.originOffsets.y = transform.height;
			break;
		case Enum::OriginPoint::CENTER:
		default:
			event.originOffsets.x = transform.width / 2.0;
			event.originOffsets.y = transform.height / 2.0;
			break;
		}

		std::cout << "x: " << (event.originOffsets.x / sprite.body->getScale().x) << "\n";
		std::cout << "y: " << (event.originOffsets.y / sprite.body->getScale().y) << "\n";

		sprite.body->setOrigin
		(
			sf::Vector2f
			(
				event.originOffsets.x / sprite.body->getScale().x,
				event.originOffsets.y / sprite.body->getScale().y
			)
		);
	}
	void setColor(Event::SetColor event)
	{
		if (event.target == NULL_ENTITY) throw std::runtime_error("Error: null entity");

		auto& spriteArray = nc().getComponentArray<Component::Sprite>();

		if (!spriteArray->hasData(event.target))
		{
			return;
		}

		auto& sprite = spriteArray->getData(event.target);

		sprite.body->setColor(event.color.data);
	}
	void loadSprite(Event::LoadSprite event)
	{
		if (event.target == NULL_ENTITY) throw std::runtime_error("Error: null entity");

		auto& transformArray = nc().getComponentArray<Component::Transform>();
		auto& textureArray = nc().getComponentArray<Component::Texture>();

		if (!transformArray->hasData(event.target) ||
			!textureArray->hasData(event.target))
		{
			return;
		}

		auto& texture = textureArray->getData(event.target);
		auto& transform = transformArray->getData(event.target);

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
	void setTextString(Event::SetTextString event)
	{
		if (event.target == NULL_ENTITY) throw std::runtime_error("Error: null entity");

		event.text->setString(event.string);
	}
	void setTextSize(Event::SetTextSize event)
	{
		if (event.target == NULL_ENTITY) throw std::runtime_error("Error: null entity");

		event.text->setCharacterSize(event.size);
	}
	void setTextColor(Event::SetTextColor event)
	{
		if (event.target == NULL_ENTITY) throw std::runtime_error("Error: null entity");

		event.text->setFillColor(event.color);
	}
	void clickedButton(Event::MouseClick event)
	{
		auto& buttonArray = nc().getComponentArray<Component::Button>();
		auto& originArray = nc().getComponentArray<Component::OriginOffsets>();
		auto& transformArray = nc().getComponentArray<Component::Transform>();
		auto& positionArray = nc().getComponentArray<Component::Position>();

		for (auto& [entity, button] : buttonArray->getAll())
		{
			if (button.state == Enum::ButtonState::CLICKED ||
				!button.enabled ||
				!originArray->hasData(entity) ||
				!positionArray->hasData(entity) ||
				!transformArray->hasData(entity))
			{
				continue;
			}

			const auto& originOffset = originArray->getData(entity);
			const auto& transform = transformArray->getData(entity);
			const auto& pos = positionArray->getData(entity);

			if (checkCollision
			(
				event.pos,
				sf::Vector2f
				{
					static_cast<float>(pos.x - originOffset.x + (transform.width / 2.f)),
					static_cast<float>(pos.y - originOffset.y + (transform.height / 2.f))
				},
				sf::Vector2f
				{
					0.f,
					0.f
				},
				sf::Vector2f
				{
					static_cast<float>(transform.width),
					static_cast<float>(transform.height)
				}
			)
				)
			{
				button.timer = button.clickedAnimationDuration;
				button.state = Enum::ButtonState::CLICKED;
			}
		}
	}
	void hoverButton(Event::MouseMoved event)
	{
		auto& buttonArray = nc().getComponentArray<Component::Button>();
		auto& originArray = nc().getComponentArray<Component::OriginOffsets>();
		auto& transformArray = nc().getComponentArray<Component::Transform>();
		auto& positionArray = nc().getComponentArray<Component::Position>();

		for (auto& [entity, button] : buttonArray->getAll())
		{
			if (button.timer > 0.0 ||
				button.state == Enum::ButtonState::HOVERED ||
				button.state == Enum::ButtonState::CLICKED ||
				!button.enabled ||
				!originArray->hasData(entity) ||
				!positionArray->hasData(entity) ||
				!transformArray->hasData(entity))
			{
				continue;
			}

			const auto& originOffset = originArray->getData(entity);
			const auto& transform = transformArray->getData(entity);
			const auto& pos = positionArray->getData(entity);

			if (checkCollision
			(
				event.pos,
				sf::Vector2f
				{
					static_cast<float>(pos.x - originOffset.x + (transform.width / 2.f)),
					static_cast<float>(pos.y - originOffset.y + (transform.height / 2.f))
				},
				sf::Vector2f
				{
					0.f,
					0.f
				},
				sf::Vector2f
				{
					static_cast<float>(transform.width),
					static_cast<float>(transform.height)
				}
			)
				)
			{
				button.timer = button.hoverAnimationDuration;
				button.state = Enum::ButtonState::HOVERED;
			}
		}
	}
	void idleButton(Event::MouseMoved event)
	{
		auto& buttonArray = nc().getComponentArray<Component::Button>();
		auto& originArray = nc().getComponentArray<Component::OriginOffsets>();
		auto& transformArray = nc().getComponentArray<Component::Transform>();
		auto& positionArray = nc().getComponentArray<Component::Position>();

		for (auto& [entity, button] : buttonArray->getAll())
		{
			if (button.timer > 0.0 ||
				button.state == Enum::ButtonState::IDLE ||
				button.state == Enum::ButtonState::CLICKED ||
				!button.enabled ||
				!originArray->hasData(entity) ||
				!positionArray->hasData(entity) ||
				!transformArray->hasData(entity))
			{
				continue;
			}

			const auto& originOffset = originArray->getData(entity);
			const auto& transform = transformArray->getData(entity);
			const auto& pos = positionArray->getData(entity);

			if (checkCollision
			(
				event.pos,
				sf::Vector2f
				{
					static_cast<float>(pos.x - originOffset.x + (transform.width / 2.f)),
					static_cast<float>(pos.y - originOffset.y + (transform.height / 2.f))
				},
				sf::Vector2f
				{
					0.f,
					0.f
				},
				sf::Vector2f
				{
					static_cast<float>(transform.width),
					static_cast<float>(transform.height)
				}
			)
				)
			{
				continue;
			}

			button.timer = button.idleAnimationDuration;
			button.state = Enum::ButtonState::IDLE;
		}
	}
	void playNextScene(Event::PlayScene event)
	{
		nc().destroyAll();
		playScene(event.next);
	}
}