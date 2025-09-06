#include "Headers/Systems.h"

const float PLAYER_MOVE_SPEED = 200.0f;

void InputSystem(ComponentManager& cm,
	Entity player)
{
	Velocity& vel = cm.getComponent<Velocity>(player);
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

void MovementSystem(ComponentManager& cm,
	DeltaTime dt)
{
	auto& velocities = cm.getComponentArray<Velocity>()->getAll();

	for (auto& [entity, vel] : velocities)
	{
		if (cm.getComponentArray<Position>()->hasData(entity))
		{
			Position& pos = cm.getComponent<Position>(entity);
			pos.x += (vel.dx * dt);
			pos.y += (vel.dy * dt);
		}
	}
}

void RenderSystem(RenderWindow& window,
	ComponentManager& cm)
{

	auto& shapes = cm.getComponentArray<ShapeComponent>()->getAll();

	for (auto& [entity, shape] : shapes)
	{
		if (cm.getComponentArray<ShapeComponent>()->hasData(entity))
		{
			Position pos = cm.getComponent<Position>(entity);
			shape.rect.setPosition(pos.x, pos.y);
			window.draw(shape.rect);
		}
	}
}