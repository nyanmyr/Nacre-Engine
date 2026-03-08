#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include <SFML/Graphics.hpp>

using sf::RectangleShape;

struct CPosition
{
	float x, y;
};

struct CShape
{
	RectangleShape rect;
};

#endif