#ifndef COMPONENT_ARRAY_H
#define COMPONENT_ARRAY_H

#include "EntityManager.h"
#include <unordered_map>

template<typename T>
class ComponentArray
{
private:
	unordered_map<Entity, T> components;

public:
	void insertData(Entity entity, T component)
	{
		components[entity] = component;
	}

	void removeData(Entity entity)
	{
		components.erase(entity);
	}

	T& getData(Entity entity)
	{
		return components.at(entity);
	}

	bool hasData(Entity entity)
	{
		return components.find(entity) != components.end();
	}

	unordered_map<Entity, T>& getAll()
	{
		return components;
	}
};

#endif