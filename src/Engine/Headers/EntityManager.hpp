#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include "Dependencies.hpp"

using namespace std;

const Entity MAX_ENTITIES = 10;

class EntityManager
{
private:
	queue<Entity> availableEntities;
	vector<bool> alive;
	Entity livingCount = 0;

	EntityManager();

	EntityManager(const EntityManager&) = delete;
	EntityManager& operator=(const EntityManager&) = delete;
public:
	static EntityManager& getInstance();

	Entity createEntity();
	void destroyEntity(Entity entity);

	bool isAlive(Entity entity) const;
};

#endif