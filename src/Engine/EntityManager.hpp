#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include "Dependencies.hpp"

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
		if (!alive[entity])
		{
			throw runtime_error("entity is already dead.");
		}

		alive[entity] = false;
		availableEntities.push(entity);
		livingCount--;
	}

	bool isAlive(Entity entity) const
	{
		return alive[entity];
	}
};

#endif