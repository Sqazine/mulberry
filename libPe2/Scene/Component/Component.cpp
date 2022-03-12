#include "Component.h"
#include "../Entity.h"

namespace Pe2
{

	std::string Component::mComponentType = "Component";

	Component::Component(int32_t updateOrder)
		: mUpdateOrder(updateOrder)
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
		return mUpdateOrder;
	}

	Entity *Component::GetOwner() const
	{
		return mOwner;
	}

	bool Component::IsSameComponentType(const std::string &componentType) const
	{
		return mComponentType == componentType;
	}
}