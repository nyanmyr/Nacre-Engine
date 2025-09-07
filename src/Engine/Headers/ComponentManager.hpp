#ifndef COMPONENTS_MANAGER_H
#define COMPONENTS_MANAGER_H

#include <unordered_map>
#include <memory>
#include <stdexcept>

using namespace std;

class ComponentManager
{
private:
	unordered_map<const char*, shared_ptr<IComponentArray>> componentsArray;

	ComponentManager() {};

	ComponentManager(const ComponentManager&) = delete;
	ComponentManager& operator=(const ComponentManager&) = delete;
public:
	template<typename T>
	void registerComponent()
	{
		const char* typeName = typeid(T).name();

		if ((componentsArray.find(typeName)) != componentsArray.end())
		{
			throw runtime_error("Component already registered.");
		}

		componentsArray.insert({ typeName, make_shared<ComponentArray<T>>() });
	}

	template<typename T>
	void addComponent(Entity entity, T component)
	{
		getComponentArray<T>()->insertData(entity, component);
	}

	template<typename T>
	void removeComponent(Entity entity)
	{
		getComponentArray<T>()->removeData(entity);
	}

	template<typename T>
	T& getComponent(Entity entity)
	{
		return getComponentArray<T>()->getData(entity);
	}

	void entityDestroyed(Entity entity)
	{
		for (auto const& pair : componentsArray)
		{
			pair.second->destroyComponents(entity);
		}
	}

	template<typename T>
	shared_ptr<ComponentArray<T>> getComponentArray()
	{
		const char* typeName = typeid(T).name();

		auto it = componentsArray.find(typeName);
		if (it == componentsArray.end())
		{
			throw runtime_error("Component not registered.");
		}

		return static_pointer_cast<ComponentArray<T>>(it->second);
	}

	static ComponentManager& getInstance()
	{
		static ComponentManager instance;
		return instance;
	}
};

#endif