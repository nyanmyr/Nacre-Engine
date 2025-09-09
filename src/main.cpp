#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>

#include "Engine/Headers/ComponentArray.hpp"
#include "Engine/Headers/EntityManager.hpp"
#include "Engine/Headers/ComponentManager.hpp"

using namespace std;
using namespace sf;

using DeltaTime = float;

//  components
#pragma region Components
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
#pragma endregion

#pragma region Systems Declarations

void SpawnerSystem(DeltaTime dt);
void PlayerInputSystem(Entity player);
void MovementSystem(DeltaTime dt);
void KeyboardInputSystem(RenderWindow& window);
void RenderSystem(RenderWindow& window);
void HandleLifetimeSystem(DeltaTime time);

#pragma endregion


// global variables
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

const int MAX_FPS = 60;

const float PLAYER_MOVE_SPEED = 200.f;
const float SPAWN_COOLDOWN = 3.f;

EntityManager& em = EntityManager::getInstance();
ComponentManager& cm = ComponentManager::getInstance();

int main()
{
	RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Nacre Engine", Style::Close);
	window.setFramerateLimit(MAX_FPS);

	// register components
	cm.registerComponent<CPosition>();
	cm.registerComponent<CLineSegment>();
	cm.registerComponent<CVelocity>();
	cm.registerComponent<CShape>();
	//cm.registerComponent<Collision>();
	cm.registerComponent<CLifeTime>();
	cm.registerComponent<CZIndex>();

	// entity initialization
	

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

		// input systems
		//PlayerInputSystem(GetPlayerID());

		// update systems
		//SpawnerSystem(dt);

		MovementSystem(dt);

		KeyboardInputSystem(window);

		HandleLifetimeSystem(dt);

		window.clear();
		// render systems
		RenderSystem(window);
		window.display();
	}

	return 0;
}

#pragma region systems definitions

void SpawnerSystem(DeltaTime dt)
{
	static float timer;
	timer += dt;

	if (timer > SPAWN_COOLDOWN)
	{
		Entity box = em.createEntity();
		cm.addComponent(
			box,
			CPosition{
				100.0f,
				100.0f
			}
		);
		cm.addComponent(
			box,
			CShape{
				RectangleShape(Vector2f(50.0f,50.0f))
			}
		);
		cm.addComponent(
			box,
			CLifeTime{
				0.f,
				1.5f
			}
		);
		cm.addComponent(
			box,
			CZIndex{
				0
			}
		);
		cm.addComponent(
			box,
			CZIndex{
				0
			}
		);

		timer = 0.f;
	}
}

void PlayerInputSystem(Entity player)
{
	CVelocity& vel = cm.getComponent<CVelocity>(player);
	vel.dx = 0.0f;
	vel.dy = 0.0f;

	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		vel.dx = -PLAYER_MOVE_SPEED;
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		vel.dx = PLAYER_MOVE_SPEED;
	}
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		vel.dy = -PLAYER_MOVE_SPEED;
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		vel.dy = PLAYER_MOVE_SPEED;
	}
}

void MovementSystem(DeltaTime dt)
{
	auto& velocities = cm.getComponentArray<CVelocity>()->getAll();

	for (auto& [entity, vel] : velocities)
	{
		if (cm.getComponentArray<CPosition>()->hasData(entity))
		{
			CPosition& pos = cm.getComponent<CPosition>(entity);
			pos.x += (vel.dx * dt);
			pos.y += (vel.dy * dt);
		}
	}
}

void KeyboardInputSystem(RenderWindow& window)
{
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::KeyReleased)
		{
			if (event.key.code == Keyboard::Space)
			{
			}
		}
	}
}

void HandleLifetimeSystem(DeltaTime dt)
{
	auto& lifetimes = cm.getComponentArray<CLifeTime>()->getAll();

	vector<Entity> toDelete;

	for (auto& [entity, lifetime] : lifetimes)
	{
		lifetime.lifeTime += dt;
		if (lifetime.lifeTime >= lifetime.deathTime)
		{
			toDelete.push_back(entity);
		}
	}

	if (toDelete.empty())
	{
		return;
	}

	for (Entity entity : toDelete)
	{
		cm.entityDestroyed(entity);
		em.destroyEntity(entity);
	}
}

void RenderSystem(RenderWindow& window)
{
	map<int, map<Entity, vector<CLineSegment>>> lineOrder;
	map<int, map<Entity, vector<CShape>>> shapeOrder;

	auto& shapes = cm.getComponentArray<CShape>()->getAll();
	auto& lines = cm.getComponentArray<CLineSegment>()->getAll();

	auto& zIndices = cm.getComponentArray<CZIndex>()->getAll();

	//cout << "Size: " << shapes.size() << "\n";
	//cout << "Size: " << zIndices.size() << "\n";

	for (auto& [entity, line] : lines)
	{
		int zIndex = zIndices.at(entity).index;
		//cout << "index: " << zIndex << "\n";
		lineOrder[zIndex][entity].push_back(line);
	}

	for (auto& [entity, shape] : shapes)
	{
		int zIndex = zIndices.at(entity).index;
		//cout << "index: " << zIndex << "\n";
		shapeOrder[zIndex][entity].push_back(shape);
	}

	//cout << "line indexes:" << lineOrder.size() << "\n";
	//cout << "indexes:" << order.size() << "\n";

	if (!lineOrder.empty())
	{
		map<int, map<Entity, vector<CLineSegment>>>::iterator lineIter;
		for (lineIter = lineOrder.begin(); lineIter != lineOrder.end(); ++lineIter)
		{
			int zIndex = lineIter->first;
			//cout << "index:" << zIndex << "\n";

			for (auto& pair : lineOrder[zIndex]) // loops through each entity and vector pair
			{
				vector<CLineSegment>::iterator vectorsIter;
				for (vectorsIter = pair.second.begin(); vectorsIter != pair.second.end(); ++vectorsIter) // loops through each vector
				{
					vector<Vector2f> points = vectorsIter->points;
					//cout << "points: " << points.size() << "\n";
					VertexArray lineStrip(LinesStrip, points.size());
					for (size_t point = 0; point < points.size(); ++point)
					{
						lineStrip[point].position = Vector2f(points[point].x, points[point].y);
						lineStrip[point].color = Color::Yellow;
					}
					window.draw(lineStrip);
				}
				//cout << "\n";
			}
		}
	}

	if (!shapeOrder.empty())
	{
		map<int, map<Entity, vector<CShape>>>::iterator iter;
		for (iter = shapeOrder.begin(); iter != shapeOrder.end(); ++iter)
		{
			int zIndex = iter->first;
			//cout << "index:" << zIndex << "\n";
			for (auto& pair : shapeOrder[zIndex])
			{
				auto& pos = cm.getComponent<CPosition>(pair.first);
				pair.second[0].rect.setPosition(pos.x, pos.y);
				window.draw(pair.second[0].rect);
			}
		}
	}
}

#pragma endregion