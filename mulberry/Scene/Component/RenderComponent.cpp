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

	void RenderComponent::SetMaterial(RasterMaterial *mat)
	{
		material.reset(mat);
	}
	const RasterMaterial *RenderComponent::GetMaterial() const
	{
		return material.get();
	}
}