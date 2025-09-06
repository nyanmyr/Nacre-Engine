#include <iostream>
#include "Engine/Headers/Components.h"
#include "Engine/Headers/EntityManager.h"
#include "Engine/Headers/ComponentArray.h"
#include "Engine/Headers/Systems.h"
#include "Engine/Headers/ComponentManager.h"

using namespace std;
using namespace sf;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

EntityManager& em = EntityManager::getInstance();
ComponentManager& cm = ComponentManager::getInstance();

//class Player
//{
//public:
//	Player(
//		ComponentArray<Position>& positions,
//		ComponentArray<Velocity>& velocities,
//		ComponentArray<ShapeComponent>& shapes,
//		struct Position position,
//		struct Velocity velocity,
//		struct ShapeComponent shape
//	)
//	{
//		playerID = entityManager.createEntity();
//		positions.insertData
//		(
//			playerID,
//			position
//		);
//		velocities.insertData
//		(
//			playerID,
//			velocity
//		);
//		shapes.insertData
//		(
//			playerID,
//			shape
//		);
//		shapes.getData(playerID).rect.setFillColor(Color::Green);
//	}
//
//	Entity getEntityID()
//	{
//		return playerID;
//	}
//
//private:
//	Entity playerID;
//	Position position;
//	Velocity velocity;
//	ShapeComponent shape;
//};

int main()
{
	RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML Basics");
	window.setFramerateLimit(60);

	cm.registerComponent<Position>();
	cm.registerComponent<Velocity>();
	cm.registerComponent<ShapeComponent>();

	Entity player = em.createEntity();
	cm.addComponent
	(
		player,
		Position{
			0.0f,
			0.0f
		}
	);
	cm.addComponent
	(
		player,
		Velocity{
			0.0f,
			0.0f
		}
	);
	cm.addComponent
	(
		player,
		ShapeComponent{
			RectangleShape(Vector2f(50.0f,50.0f))
		}
	);

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
		InputSystem(cm, player);

		// update systems
		MovementSystem(cm, dt);

		window.clear();
		// render systems
		RenderSystem(window, cm);
		window.display();
	}

	return 0;
}