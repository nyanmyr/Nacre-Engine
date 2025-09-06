#ifndef SYSTEMS_H
#define SYSTEMS_H

#include "ComponentArray.h"
#include "Components.h"
#include "ComponentManager.h"

using DeltaTime = float;

void InputSystem(ComponentManager& cm,
	Entity player);
void MovementSystem(ComponentManager& cm,
	DeltaTime dt);
void RenderSystem(RenderWindow& window,
	ComponentManager& cm);

#endif