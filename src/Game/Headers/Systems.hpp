#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP

#include <SFML/Graphics.hpp>
#include "../../Engine/NacreCoordinator.hpp"
#include "Components.hpp"

// oughta make some of these parameters as consts

// -------------------------------------------------------
// start systems
// -------------------------------------------------------
void SetTextSystem(sf::Font font);
void SetTextOriginSystem();
void SetShapeOriginSystem();

// -------------------------------------------------------
// update systems
// -------------------------------------------------------
void ButtonClickedSystem(sf::Vector2i&, bool&, DeltaTime);
void NextSceneSystem(sf::RenderWindow&, sf::Font&);
void PlayerControlSystem(const Entity player, DeltaTime dt);
void MoveSystem(const DeltaTime dt);
void DragSystem(const DeltaTime dt);

// make edge collision system here

// -------------------------------------------------------
// rendering systems
// -------------------------------------------------------
void ZIndexSystem(std::queue<Entity>&);
void RenderSystem(sf::RenderWindow&, std::queue<Entity>&);

#endif
