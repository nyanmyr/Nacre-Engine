#ifndef SYSTEMS_H
#define SYSTEMS_H

#include "ComponentArray.h"
#include "Components.h"

using DeltaTime = float;

void MovementSystem(ComponentArray<Position>& positions,
	ComponentArray<Velocity>& velocities,
	DeltaTime dt);
void RenderSystem(RenderWindow& window,
	ComponentArray<Position>& positions,
	ComponentArray<ShapeComponent>& shapes);
void InputSystem(ComponentArray<Velocity>& velocities,
	Entity player);

#endif