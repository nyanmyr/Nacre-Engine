#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <SFML/Graphics.hpp>

using namespace sf;

struct CPosition
{
	float x;
	float y;
};

struct CVelocity
{
	float dx, dy;
};

struct CShape
{
	RectangleShape rect;
};

struct CCollision
{
	bool canCollide;
};

struct CLifeTime
{
	float lifeTime;
	float deathTime;
};

struct CZIndex
{
	int index;
};

#endif