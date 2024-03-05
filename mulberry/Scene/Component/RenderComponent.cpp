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

	void RenderComponent::SetMaterial(GraphicsMaterial *mat)
	{
		material.reset(mat);
	}
	const GraphicsMaterial *RenderComponent::GetMaterial() const
	{
		return material.get();
	}
}