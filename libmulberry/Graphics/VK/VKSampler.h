#pragma once
#include <vulkan/vulkan.h>
#include "Graphics/Texture.h"

namespace mulberry 
{
	enum FilterType
	{
		NEAREST = VK_FILTER_NEAREST,
		LINEAR = VK_FILTER_LINEAR,
		MIPMAP_NEAREST = VK_SAMPLER_MIPMAP_MODE_NEAREST,
		MIPMAP_LINEAR = VK_SAMPLER_MIPMAP_MODE_LINEAR,
	};

	enum AddressType
	{
		REPEAT = VK_SAMPLER_ADDRESS_MODE_REPEAT,
		MIRRORED_REPEAT = VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT,
		CLAMP_TO_EDGE = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
		CLAMP_TO_BORDER = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER,
	};

	class VKSampler
	{
	public:
		VKSampler(FilterType magFilter, FilterType minFilter, AddressType addressU, AddressType addressV, AddressType addressW);
		~VKSampler();

		const VkSampler& GetHandle() const;

	private:
		VkSampler mHandle;
	};
}
