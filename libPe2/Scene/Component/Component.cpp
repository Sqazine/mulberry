#include "Component.h"
#include "../Entity.h"

namespace Pe2
{

	std::string Component::m_ComponentType = "Component";

	Component::Component(int32_t updateOrder)
		: m_UpdateOrder(updateOrder)
	{
	}

	Component::~Component()
	{
	}

	void Component::Init()
	{

	}

	void Component::ProcessInput(const InputDevice* inputDevice)
	{
	}
	void Component::Update(float deltaTime)
	{
	}

	void Component::LateUpdate(float deltaTime)
	{
	}
	void Component::FixedUpdate()
	{
	}

	int32_t Component::GetUpdateOrder() const
	{
		return m_UpdateOrder;
	}

	Entity *Component::GetOwner() const
	{
		return m_Owner;
	}

	bool Component::IsSameComponentType(const std::string &componentType) const
	{
		return m_ComponentType == componentType;
	}
}