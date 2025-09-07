#include "Headers/Systems.hpp"

const float PLAYER_MOVE_SPEED = 200.f;

const float SPAWN_COOLDOWN = 3.f;

EntityManager& emSystems = EntityManager::getInstance();
ComponentManager& cmSystems = ComponentManager::getInstance();

void SpawnerSystem(DeltaTime dt)
{
	static float timer;
	timer += dt;

	if (timer > SPAWN_COOLDOWN)
	{
		Entity box = emSystems.createEntity();
		cmSystems.addComponent(
			box,
			CPosition{
				100.0f,
				100.0f
			}
		);
		cmSystems.addComponent(
			box,
			CShape{
				RectangleShape(Vector2f(50.0f,50.0f))
			}
		);
		cmSystems.addComponent(
			box,
			CLifeTime{
				0.f,
				1.5f
			}
		);
		cmSystems.addComponent(
			box,
			CZIndex{
				0
			}
		);
		cmSystems.addComponent(
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
	CVelocity& vel = cmSystems.getComponent<CVelocity>(player);
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
	auto& velocities = cmSystems.getComponentArray<CVelocity>()->getAll();

	for (auto& [entity, vel] : velocities)
	{
		if (cmSystems.getComponentArray<CPosition>()->hasData(entity))
		{
			CPosition& pos = cmSystems.getComponent<CPosition>(entity);
			pos.x += (vel.dx * dt);
			pos.y += (vel.dy * dt);
		}
	}
}

void HandleLifetimeSystem(DeltaTime dt)
{
	auto& lifetimes = cmSystems.getComponentArray<CLifeTime>()->getAll();

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
		cmSystems.entityDestroyed(entity);
		emSystems.destroyEntity(entity);
	}
}

void RenderSystem(RenderWindow& window)
{
	map<int, map<Entity, vector<CShape>>> order;
	auto& shapes = cmSystems.getComponentArray<CShape>()->getAll();
	auto& zIndices = cmSystems.getComponentArray<CZIndex>()->getAll();

	//cout << "Size: " << shapes.size() << "\n";
	//cout << "Size: " << zIndices.size() << "\n";

	for (auto& [entity, shape] : shapes)
	{
		int zIndex = zIndices.at(entity).index;
		//cout << "index: " << zIndex << "\n";
		order[zIndex][entity].push_back(shape);
	}

	//cout << "indexes:" << order.size() << "\n";

	if (order.empty())
	{
		return;
	}

	map<int, map<Entity, vector<CShape>>>::iterator iter;
	for (iter = order.begin(); iter != order.end(); ++iter)
	{
		int zIndex = iter->first;
		//cout << "index:" << zIndex << "\n";
		for (auto& pair : order[zIndex])
		{
			auto& pos = cmSystems.getComponent<CPosition>(pair.first);
			pair.second[0].rect.setPosition(pos.x, pos.y);
			window.draw(pair.second[0].rect);
		}
	}
}