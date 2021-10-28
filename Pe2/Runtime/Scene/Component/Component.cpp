#include "Component.h"
#include "../Entity.h"
std::string Component::m_ComponentType = "Component";

Component::Component(int updateOrder)
	:m_UpdateOrder(updateOrder)
{
}

Component::~Component()
{
}

void Component::Update(float deltaTime)
{
}

int Component::GetUpdateOrder() const
{
	return m_UpdateOrder;
}

Entity* Component::GetOwner() const
{
	return m_Owner;
}

bool Component::IsSameComponentType(const std::string& componentType) const
{
	return m_ComponentType==componentType;
}