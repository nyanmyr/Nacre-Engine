#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

enum MouseEvent {
	NOTHING,
	START_GAME
};

struct CPosition
{
	float x, y;
};

struct CShape
{
	RectangleShape rect;
};

struct CButton
{
	MouseEvent mouseEvent;
};

struct CSprite
{
	Texture texture;
	Sprite sprite;
};

struct CMouseAim
{
	float rotation;
};

struct CVelocity
{
	float dx, dy;
};

#endif