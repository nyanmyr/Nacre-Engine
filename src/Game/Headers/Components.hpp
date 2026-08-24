#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include <SFML/Graphics.hpp>
#include "Scenes.hpp"
#include "Enums.hpp"
#include <optional>
#include <string>

struct CPosition
{
	double x = 0.f;
	double y = 0.f;
};

struct CTransform
{
	double width = 0.f;
	double height = 0.f;
};

struct COrigin
{
	double offsetX = 0.f;
	double offsetY = 0.f;
};

struct CButton
{
	double clickedDuration = 0.f;
	double enabled = true;
	double clickedTimer = 0.f;
	bool clicked = false;
};

struct CText
{
	std::optional<sf::Text> box {};
	std::string string = "";
	int size = 12;
	sf::Color color = sf::Color::White;
	Enum::TextFormat format = Enum::TextFormat::MIDDLE;
};

struct CNextScene
{
	Scene next = Scene::MENU;
	bool active = false;
};

struct CZIndex
{
	int index = 0;
	bool visible = true;
};

struct CVelocity
{
	double minX = 0.f;
	double minY = 0.f;
	double maxX = 0.f;
	double maxY = 0.f;
	double x = 0.f;
	double y = 0.f;
};

struct CSpeed
{
	double x = 0.f;
	double y = 0.f;
};

struct CPlayerController
{
	bool enabled = false;
};

struct CDrag
{
	double x = 0.f;
	double y = 0.f;
};

struct CSprite
{
	std::optional<sf::Sprite> body {};
};

struct CTexture
{
	Enum::Texture data;
};

struct CTexturesContainer
{
	std::unordered_map<Enum::Texture, sf::Texture> map;
};

struct CColor
{
	sf::Color col = sf::Color(sf::Color::White);
};


#endif