#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP

const float PLAYER_MOVE_SPEED = 200.f;

EntityManager& em = EntityManager::getInstance();
ComponentManager& cm = ComponentManager::getInstance();

void RenderSystem(RenderWindow& window)
{
	auto& shapes = cm.getComponentArray<CShape>();
	auto& positions = cm.getComponentArray<CPosition>();

	for (auto& [entity, shape] : shapes->getAll())
	{
		if (positions->hasData(entity))
		{
			CPosition pos = positions->getData(entity);
			shape.rect.setPosition(pos.x, pos.y);
			window.draw(shape.rect);
		}
	}
}

void RenderSprites(RenderWindow& window)
{
	auto& sprites = cm.getComponentArray<CSprite>();
	auto& positions = cm.getComponentArray<CPosition>();

	for (auto& [entity, sprite] : sprites->getAll())
	{
		if (positions->hasData(entity))
		{
			CPosition pos = positions->getData(entity);
			Sprite& entitySprite = sprite.sprite;
			// centers the sprite relative to position
			entitySprite.setPosition(
				pos.x,
				pos.y
			);
			window.draw(sprite.sprite);
		}
	}
}

MouseEvent MouseClickSystem(Vector2f mousePosition)
{
	//cout << "x: " << mousePosition.x << " y: " << mousePosition.y << "\n";

	auto& shapes = cm.getComponentArray<CShape>();
	auto& buttons = cm.getComponentArray<CButton>();

	for (auto& [entity, button] : buttons->getAll())
	{
		if (!shapes->hasData(entity))
		{
			// skip if the button does not have a shape
			continue;
		}

		if (buttons->hasData(entity))
		{
			sf::FloatRect buttonBounds = shapes->getData(entity).rect.getGlobalBounds();
			Vector2f buttonPositions = buttonBounds.getPosition();
			if (buttonBounds.contains(mousePosition))
			{
				return MouseEvent::START_GAME;
			}
		}
	}

	return MouseEvent::NOTHING;
}

void PlayerAim(Vector2i mousePosition)
{
	auto& aims = cm.getComponentArray<CMouseAim>();
	auto& sprites = cm.getComponentArray<CSprite>();
	auto& positions = cm.getComponentArray<CPosition>();

	for (auto& [entity, aimer] : aims->getAll())
	{
		if (!positions->hasData(entity))
		{
			// if the aimer does not have a position then skip
			continue;
		}

		if (sprites->hasData(entity))
		{
			CPosition entityPosition = positions->getData(entity);
			Sprite& entitySprite = sprites->getData(entity).sprite;

			float x = mousePosition.x - entityPosition.x;
			float y = mousePosition.y - entityPosition.y;

			float degrees = atan2f(y, x) * (180.f / 3.14159265358979323846f);

			entitySprite.setRotation(degrees);
		}
	}
}

void PlayerInputSystem(Entity player)
{
	CVelocity& vel = cm.getComponent<CVelocity>(player);
	vel.dx = 0.0f;
	vel.dy = 0.0f;

	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		vel.dx = -PLAYER_MOVE_SPEED;
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		vel.dx = PLAYER_MOVE_SPEED;
	}
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		vel.dy = -PLAYER_MOVE_SPEED;
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		vel.dy = PLAYER_MOVE_SPEED;
	}
}

void MovementSystem(DeltaTime dt)
{
	auto& velocities = cm.getComponentArray<CVelocity>()->getAll();

	for (auto& [entity, vel] : velocities)
	{
		if (cm.getComponentArray<CPosition>()->hasData(entity))
		{
			CPosition& pos = cm.getComponent<CPosition>(entity);
			pos.x += (vel.dx * dt);
			pos.y += (vel.dy * dt);
		}
	}
}

#endif
