#pragma once
#include "Component.h"
class SpriteComponent:public Component
{
	COMPONENT_DECLARATION()
public:
	SpriteComponent();
	~SpriteComponent();
};