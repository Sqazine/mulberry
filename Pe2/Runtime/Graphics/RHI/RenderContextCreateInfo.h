#pragma once
#include "../../Window.h"

enum class RenderBackend
{
	GL,
	VK,
};

struct RenderContextCreateInfo
{
	WindowCreateInfo windowCreateInfo;
	RenderBackend backend = RenderBackend::VK;
	bool useDoubleBuffering = true;
	bool useVSync = false;
};