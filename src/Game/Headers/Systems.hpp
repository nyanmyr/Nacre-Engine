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
void ButtonClickedSystem(sf::Vector2i&, bool&, DeltaTime);
void NextSceneSystem(sf::RenderWindow&, sf::Font&);

// -------------------------------------------------------
// rendering systems
// -------------------------------------------------------
void ZIndexSystem(std::queue<Entity>&);
void RenderSystem(sf::RenderWindow&, std::queue<Entity>&);

#endif
