#include "Component.h"
#include "Entity.h"
#include "Scene.h"
#include "AssetManager.h"
namespace mulberry
{
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

	void Component::Update()
	{
	}

	void Component::LateUpdate()
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

	Scene *Component::GetScene() const
	{
		return mOwner->GetOwner();
	}

	AssetManager *Component::GetSceneAssetManager() const
	{
		return GetScene()->GetSceneAssetManager();
	}
}