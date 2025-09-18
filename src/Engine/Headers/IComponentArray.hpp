#ifndef INTERFACE_COMPONENT_ARRAY_HPP
#define INTERFACE_COMPONENT_ARRAY_HPP

struct IComponentArray
{
	virtual ~IComponentArray() = default;
	virtual void destroyComponents(Entity entity) = 0;
};

#endif
