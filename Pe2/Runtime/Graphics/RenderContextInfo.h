#pragma once
#include "../Platform/Window.h"

namespace Pe2
{

	enum class RenderBackend
	{
		GL,
		VK,
	};

	enum RenderFlag
	{
		DOUBLE_BUFFERING = 1,
		VSYNC = 2
	};

	struct RenderContextInfo
	{
		WindowInfo windowInfo;
		RenderBackend backend = RenderBackend::GL;
		int flag = DOUBLE_BUFFERING | VSYNC;
	};
}