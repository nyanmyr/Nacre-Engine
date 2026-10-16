#ifndef ENUMS_HPP
#define ENUMS_HPP

namespace Enum
{
	enum class TextFormat
	{
		TOP,
		MIDDLE,
		BOTTOM,
	};

	enum class Texture
	{
		TEXTURE_PLACEHOLDER,
	};

	enum class ButtonState
	{
		IDLE,
		HOVERED,
		CLICKED,
	};

	enum class OriginPoint
	{
		LEFT,
		RIGHT,
		TOP,
		BOTTOM,
		TOP_LEFT,
		TOP_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_RIGHT,
		CENTER,
	};
}

#endif