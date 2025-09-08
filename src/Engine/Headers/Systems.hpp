#ifndef SYSTEMS_H
#define SYSTEMS_H

#include "ComponentArray.hpp"
#include "Components.hpp"
#include "ComponentManager.hpp"
#include "GameStateManager.hpp"

#include <cstdlib>

using namespace std;

using DeltaTime = float;

void SpawnerSystem(DeltaTime dt);
void PlayerInputSystem(Entity player);
void MovementSystem(DeltaTime dt);
void KeyboardInputSystem(RenderWindow& window);
void RenderSystem(RenderWindow& window);
void HandleLifetimeSystem(DeltaTime time);

#endif