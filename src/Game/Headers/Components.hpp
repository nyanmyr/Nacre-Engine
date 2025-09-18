#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include "Nacre.hpp"

struct CPosition
{
	float x, y;
};

struct CLineSegment
{
	vector<Vector2f> points;
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
	float lifeTime, deathTime;
};

struct CZIndex
{
	int index;
};

#endif