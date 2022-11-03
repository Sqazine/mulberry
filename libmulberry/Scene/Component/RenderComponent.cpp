#include "RenderComponent.h"
#include "Entity.h"
#include "TransformComponent.h"
namespace mulberry
{

	COMPONENT_DEFINITION(Component, RenderComponent)

	RenderComponent::RenderComponent()
		: Component()
	{
	}

	RenderComponent::~RenderComponent()
	{
	}

	void RenderComponent::Init()
	{
		REQUIRED_COMPONENT(TransformComponent)
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