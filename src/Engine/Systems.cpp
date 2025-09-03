#include "Headers/Systems.h"

const float PLAYER_MOVE_SPEED = 200.0f;

void MovementSystem(ComponentArray<Position>& positions,
	ComponentArray<Velocity>& velocities,
	DeltaTime dt)
{
	for (auto& [entity, vel] : velocities.getAll())
	{
		if (positions.hasData(entity))
		{
			Position& pos = positions.getData(entity);
			pos.x += (vel.dx * dt);
			pos.y += (vel.dy * dt);
		}
	}
}

void RenderSystem(RenderWindow& window,
	ComponentArray<Position>& positions,
	ComponentArray<ShapeComponent>& shapes)
{

	for (auto& [entity, shape] : shapes.getAll())
	{
		if (positions.hasData(entity))
		{
			Position pos = positions.getData(entity);
			shape.rect.setPosition(pos.x, pos.y);
			window.draw(shape.rect);
		}
	}
}

void InputSystem(ComponentArray<Velocity>& velocities,
	Entity player)
{
	Velocity& vel = velocities.getData(player);
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