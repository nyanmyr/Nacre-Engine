#ifndef COMPONENT_ARRAY_HPP
#define COMPONENT_ARRAY_HPP

#include "Dependencies.hpp"
#include "IComponentArray.hpp"

template<typename T>
class ComponentArray : public IComponentArray
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

	void destroyComponents(Entity entity) override
	{
		if (components.find(entity) != components.end())
		{
			components.erase(entity);
		}
	}
};

#endif