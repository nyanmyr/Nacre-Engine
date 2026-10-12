#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP

#include <SFML/Graphics.hpp>
#include "../../Engine/Core.hpp"
#include "Components.hpp"
#include <queue>

namespace Start
{
	void setText(sf::Font& font);
	void setTextOrigin();
	void setSpriteOrigin();
	void loadTextures(Component::Singleton::TexturesContainer& loadedTextures);
	void loadSprites(const Component::Singleton::TexturesContainer& loadedTextures);
	void setColor();
}

namespace Control
{
	void buttonClicks
	(
		const sf::Vector2i mouseVector,
		const DeltaTime dt
	);
	void doPlayerControl
	(
		const Entity player,
		const DeltaTime dt
	);
}

namespace Update
{
	void doButtonTimer(const DeltaTime dt);
	void applyButtonHoverAnimation();
	void applyButtonIdleAnimation();
	void doButtons
	(
		const sf::Vector2i mouseVector,
		const DeltaTime dt
	);
	void doNextScene(sf::RenderWindow& window, sf::Font& font);
	void move(const DeltaTime dt);
	void drag(const DeltaTime dt);
}

namespace Render
{
	void doZIndex(std::queue<Entity>& renderQueue);
	void render
	(
		sf::RenderWindow& window,
		std::queue<Entity>& renderQueue
	);
}

#endif
