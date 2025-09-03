#include <iostream>
#include <SFML/Graphics.hpp>
#include "Engine/Headers/Components.h"
#include "Engine/Headers/EntityManager.h"
#include "Engine/Headers/ComponentArray.h"
#include "Engine/Headers/Systems.h"

using namespace std;
using namespace sf;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

EntityManager& entityManager = EntityManager::getInstance();

int main()
{
	RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML Basics");
	window.setFramerateLimit(60);

	ComponentArray<Position> positions;
	ComponentArray<Velocity> velocities;
	ComponentArray<ShapeComponent> shapes;

	Entity player = entityManager.createEntity();
	positions.insertData
	(
		player, 
		{
			0.0f,
			0.0f
		}
	);
	velocities.insertData
	(
		player,
		{
			0.0f,
			0.0f
		}
	);
	shapes.insertData
	(
		player,
		{
			RectangleShape(Vector2f(50.0f,50.0f))
		}
	);
	shapes.getData(player).rect.setFillColor(Color::Green);

	Clock clock;

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

		// input systems
		InputSystem(velocities, player);

		// update systems
		MovementSystem(positions, velocities, dt);

		window.clear();
		// render systems
		RenderSystem(window, positions, shapes);
		window.display();
	}

	return 0;
}