#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include "../src/Engine/NacreCoordinator.hpp"
#include "Components.hpp"
#include "Systems.hpp"
#include "EntityMaker.hpp"
#include "Enums.hpp"
#include "Events.hpp"
#include "Listeners.hpp"

namespace Config
{
	inline const int SCREEN_WIDTH = 800;
	inline const int SCREEN_HEIGHT = 600;
	inline const int MAX_FPS = 60;
	inline const std::string FONT_FILEPATH = RESOURCES_PATH "arial.ttf";
	inline const std::string WINDOW_NAME = "Nacre Engine";
}

#endif
