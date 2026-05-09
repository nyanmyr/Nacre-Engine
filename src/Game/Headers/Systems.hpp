#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP

#include <SFML/Graphics.hpp>
#include "../../Engine/NacreCoordinator.hpp"
#include "Components.hpp"

// -------------------------------------------------------
// start systems
// -------------------------------------------------------
void SetTextSystem(sf::Font font);
void SetTextOriginSystem();
void SetShapeOriginSystem();

// -------------------------------------------------------
// update systems
// -------------------------------------------------------
enum MovementDirection
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	NONE
};

void ButtonClickedSystem(sf::Vector2i&, bool&, DeltaTime);
void NextSceneSystem(sf::RenderWindow&, sf::Font&);
void PlayerControlSystem(const Entity player, MovementDirection movDir, DeltaTime dt);
void MoveSystem();
// make edge collision system here

// -------------------------------------------------------
// rendering systems
// -------------------------------------------------------
void ZIndexSystem(std::queue<Entity>&);
void RenderSystem(sf::RenderWindow&, std::queue<Entity>&);

#endif
