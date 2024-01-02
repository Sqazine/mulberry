#pragma once
#include <vulkan/vulkan.h>
namespace mulberry
{
	class Viewport
	{
	public:
		Viewport(float x = 0, float y = 0, float w = 0, float h = 0)
			:x(x), y(y), width(w), height(h)
		{
		}

		~Viewport()
		{
		}

		VkViewport ToVkViewPort()
		{
			VkViewport result;
			result.x = x;
			result.y = y;
			result.width = width;
			result.height = height;
			result.minDepth = 0.0f;
			result.maxDepth = 1.0f;
			return result;
		}

		float x, y, width, height;
	};
}