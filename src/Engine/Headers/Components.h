#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <SFML/Graphics.hpp>

using namespace sf;

struct Position
{
	float x;
	float y;
};

struct Velocity
{
	float dx, dy;
};

struct ShapeComponent
{
	RectangleShape rect;
};

#endif