#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <cstdint>
#include <stdexcept>
#include <vector>
#include <queue>

using std::runtime_error;
using std::queue;
using std::vector;

using Entity = uint32_t;

const Entity MAX_ENTITIES = 10;

class EntityManager
{
private:
	queue<Entity> availableEntities;
	vector<bool> alive;
	Entity livingCount = 0;

	EntityManager()
	{
		alive.resize(MAX_ENTITIES, false);

		for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
		{
			availableEntities.push(entity);
		}
	}

	EntityManager(const EntityManager&) = delete;
	EntityManager& operator=(const EntityManager&) = delete;
public:
	static EntityManager& getInstance()
	{
		static EntityManager instance;
		return instance;
	}

	Entity createEntity()
	{
		if (livingCount >= MAX_ENTITIES)
		{
			throw runtime_error("Too many entities");
		}

		Entity id = availableEntities.front();
		availableEntities.pop();
		alive[id] = true;
		livingCount++;
		return id;
	}

	void destroyEntity(Entity entity)
	{
		try {
			alive[entity] = false;
			availableEntities.push(entity);
			livingCount--;
		}
		catch (...) {
			throw runtime_error("entity is already dead.");
		}
	}

	bool isAlive(Entity entity) const
	{
		return alive[entity];
	}
};

#endif