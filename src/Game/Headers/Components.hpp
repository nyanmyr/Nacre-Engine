#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include <SFML/Graphics.hpp>
#include "Scenes.hpp"
#include "Enums.hpp"
#include <optional>
#include <string>

namespace Component {
	struct Position;
	struct Transform;
	struct Origin;
	struct Button;
	struct Text;
	struct NextScene;
	struct ZIndex;
	struct Velocity;
	struct Speed;
	struct PlayerController;
	struct Drag;
	struct Sprite;
	struct Texture;
	struct TexturesContainer;
	struct Color;
}

struct Component::Position
{
	double x = 0.f;
	double y = 0.f;
};

struct Component::Transform
{
	double width = 0.f;
	double height = 0.f;
};

struct Component::Origin
{
	double offsetX = 0.f;
	double offsetY = 0.f;
};

struct Component::Button
{
	double clickedDuration = 0.f;
	double enabled = true;
	double clickedTimer = 0.f;
	bool clicked = false;
};

struct Component::Text
{
	std::optional<sf::Text> box {};
	std::string string = "";
	int size = 12;
	sf::Color color = sf::Color::White;
	Enum::TextFormat format = Enum::TextFormat::MIDDLE;
};

struct Component::NextScene
{
	Scene next = Scene::MENU;
	bool active = false;
};

struct Component::ZIndex
{
	int index = 0;
	bool visible = true;
};

struct Component::Velocity
{
	double minX = 0.f;
	double minY = 0.f;
	double maxX = 0.f;
	double maxY = 0.f;
	double x = 0.f;
	double y = 0.f;
};

struct Component::Speed
{
	double x = 0.f;
	double y = 0.f;
};

struct Component::PlayerController
{
	bool enabled = false;
};

struct Component::Drag
{
	double x = 0.f;
	double y = 0.f;
};

struct Component::Sprite
{
	std::optional<sf::Sprite> body {};
};

struct Component::Texture
{
	Enum::Texture data;
};

struct Component::TexturesContainer
{
	std::unordered_map<Enum::Texture, sf::Texture> map;
};

struct Component::Color
{
	sf::Color col = sf::Color(sf::Color::White);
};


#endif