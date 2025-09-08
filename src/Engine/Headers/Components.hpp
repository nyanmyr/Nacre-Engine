#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "GameStateManager.hpp"

using namespace std;

using namespace sf;

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

struct CVisibleState
{
	State state;
};

#endif