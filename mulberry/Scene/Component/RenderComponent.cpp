#include "RenderComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
namespace mulberry
{
	RenderComponent::RenderComponent()
		: Component()
	{
	}

	RenderComponent::~RenderComponent()
	{
	}

	void RenderComponent::Init()
	{
		RequiredComponent<TransformComponent>();
	}

	void RenderComponent::SetMaterial(RenderMaterial *mat)
	{
		material.reset(mat);
	}
	const RenderMaterial *RenderComponent::GetMaterial() const
	{
		return material.get();
	}
}