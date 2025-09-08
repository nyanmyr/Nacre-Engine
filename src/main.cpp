#include <iostream>
#include "Engine/Headers/Components.hpp"
#include "Engine/Headers/EntityManager.hpp"
#include "Engine/Headers/ComponentArray.hpp"
#include "Engine/Headers/Systems.hpp"
#include "Engine/Headers/ComponentManager.hpp"
#include "Engine/Headers/Initialize.hpp"
#include "Engine/Headers/GameStateManager.hpp"

using namespace std;
using namespace sf;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const int MAX_FPS = 60;

EntityManager& em = EntityManager::getInstance();
ComponentManager& cm = ComponentManager::getInstance();

int main()
{
	RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Nacre Engine", Style::Close);
	window.setFramerateLimit(MAX_FPS);

	RegisterComponents();
	Initialize();

	Clock clock;
	Clock FPSClock;

	int frameCount = 0;
	int fps = 0;

	while (window.isOpen())
	{
		DeltaTime dt = clock.restart().asSeconds();

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}

		}

		frameCount++;
		if (FPSClock.getElapsedTime().asSeconds() >= 1)
		{
			fps = frameCount;
			cout << "FPS: " << fps << "\n";
			frameCount = 0;
			FPSClock.restart();
		}

		// update systems
		SpawnerSystem(dt);

		MovementSystem(dt);

		KeyboardInputSystem(window);

		// input systems
		//PlayerInputSystem(GetPlayerID());

		HandleLifetimeSystem(dt);

		window.clear();
		// render systems
		RenderSystem(window);
		window.display();
	}

	return 0;
}