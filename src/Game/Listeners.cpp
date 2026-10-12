#include "Headers/Listeners.hpp"
#include "Headers/Components.hpp"
#include "Headers/Scenes.hpp"

#include <stdexcept>

static NacreCoordinator& nc = NacreCoordinator::getInstance();

static bool checkCollision
(
	sf::Vector2f a,
	sf::Vector2f b,
	sf::Vector2f aTrans,
	sf::Vector2f bTrans
)
{
	// AABB collision
	if (a.x + aTrans.x > b.x - bTrans.x &&
		a.x - aTrans.x < b.x + bTrans.x &&
		a.y + aTrans.y > b.y - bTrans.y &&
		a.y - aTrans.y < b.y + bTrans.y)
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

		auto& spriteArray = nc.getComponentArray<Component::Sprite>();

		if (!spriteArray->hasData(event.target))
		{
			return;
		}

		Component::Sprite& sprite = spriteArray->getData(event.target);

		sprite.body->setOrigin
		(
			sf::Vector2f
			(
				event.origin.offsetX / sprite.body->getScale().x,
				event.origin.offsetY / sprite.body->getScale().y
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
	// TODO: cleanup repetitive code
	void clickedButton(Event::MouseClick event)
	{
		auto& buttonArray = nc.getComponentArray<Component::Button>();
		auto& originArray = nc.getComponentArray<Component::Origin>();
		auto& transformArray = nc.getComponentArray<Component::Transform>();
		auto& positionArray = nc.getComponentArray<Component::Position>();

		for (auto& [entity, button] : buttonArray->getAll())
		{
			if (button.clickedTimer > 0.0 ||
				button.state == Enum::ButtonState::CLICKED ||
				!button.enabled ||
				!originArray->hasData(entity) ||
				!positionArray->hasData(entity) ||
				!transformArray->hasData(entity))
			{
				continue;
			}

			const Component::Origin& origin = originArray->getData(entity);
			const Component::Transform& transform = transformArray->getData(entity);
			const Component::Position& pos = positionArray->getData(entity);

			if (checkCollision
			(
				event.pos,
				sf::Vector2f
				{
					static_cast<float>(pos.x),
					static_cast<float>(pos.y)
				},
				sf::Vector2f
				{
					0.f,
					0.f
				},
				sf::Vector2f
				{
					static_cast<float>(transform.width - origin.offsetX),
					static_cast<float>(transform.height - origin.offsetY)
				}
			)
				)
			{
				button.clickedTimer = button.clickedDuration;
				button.state = Enum::ButtonState::CLICKED;
			}
		}
	}
	void hoverButton(Event::MouseMoved event)
	{
		auto& buttonArray = nc.getComponentArray<Component::Button>();
		auto& originArray = nc.getComponentArray<Component::Origin>();
		auto& transformArray = nc.getComponentArray<Component::Transform>();
		auto& positionArray = nc.getComponentArray<Component::Position>();

		for (auto& [entity, button] : buttonArray->getAll())
		{
			if (button.clickedTimer > 0.0 ||
				button.state == Enum::ButtonState::HOVERED ||
				button.state == Enum::ButtonState::CLICKED ||
				!button.enabled ||
				!originArray->hasData(entity) ||
				!positionArray->hasData(entity) ||
				!transformArray->hasData(entity))
			{
				continue;
			}

			const Component::Origin& origin = originArray->getData(entity);
			const Component::Transform& transform = transformArray->getData(entity);
			const Component::Position& pos = positionArray->getData(entity);

			if (checkCollision
			(
				event.pos,
				sf::Vector2f
				{
					static_cast<float>(pos.x),
					static_cast<float>(pos.y)
				},
				sf::Vector2f
				{
					0.f,
					0.f
				},
				sf::Vector2f
				{
					static_cast<float>(transform.width - origin.offsetX),
					static_cast<float>(transform.height - origin.offsetY)
				}
			)
				)
			{
				button.clickedTimer = button.clickedDuration;
				button.state = Enum::ButtonState::HOVERED;
			}
		}
	}
	void idleButton(Event::MouseMoved event)
	{
		auto& buttonArray = nc.getComponentArray<Component::Button>();
		auto& originArray = nc.getComponentArray<Component::Origin>();
		auto& transformArray = nc.getComponentArray<Component::Transform>();
		auto& positionArray = nc.getComponentArray<Component::Position>();

		for (auto& [entity, button] : buttonArray->getAll())
		{
			if (button.clickedTimer > 0.0 ||
				button.state == Enum::ButtonState::IDLE ||
				button.state == Enum::ButtonState::CLICKED ||
				!button.enabled ||
				!originArray->hasData(entity) ||
				!positionArray->hasData(entity) ||
				!transformArray->hasData(entity))
			{
				continue;
			}

			const Component::Origin& origin = originArray->getData(entity);
			const Component::Transform& transform = transformArray->getData(entity);
			const Component::Position& pos = positionArray->getData(entity);

			if (checkCollision
			(
				event.pos,
				sf::Vector2f
				{
					static_cast<float>(pos.x),
					static_cast<float>(pos.y)
				},
				sf::Vector2f
				{
					0.f,
					0.f
				},
				sf::Vector2f
				{
					static_cast<float>(transform.width - origin.offsetX),
					static_cast<float>(transform.height - origin.offsetY)
				}
			)
				)
			{
				continue;
			}

			button.clickedTimer = button.clickedDuration;
			button.state = Enum::ButtonState::IDLE;
		}
	}
	void playNextScene(Event::PlayScene event)
	{
		nc.destroyAll();
		playScene
		(
			event.window,
			event.next,
			event.font
		);
		event.window.close();
	}
}