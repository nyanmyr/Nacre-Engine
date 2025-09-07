#include "Headers/EntityManager.hpp"

EntityManager::EntityManager()
{
    alive.resize(MAX_ENTITIES, false);

    for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
    {
        availableEntities.push(entity);
    }
}

EntityManager& EntityManager::getInstance()
{
	static EntityManager instance;
	return instance;
}

Entity EntityManager::createEntity()
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

void EntityManager::destroyEntity(Entity entity)
{
	if (!alive[entity])
	{
		throw runtime_error("entity is already dead.");
	}

	alive[entity] = false;
	availableEntities.push(entity);
	livingCount--;
}

bool EntityManager::isAlive(Entity entity) const
{
	return alive[entity];
}
