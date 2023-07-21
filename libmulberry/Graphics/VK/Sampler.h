#pragma once
#include <vulkan/vulkan.h>

namespace mulberry::vk 
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

	class Sampler
	{
	public:
		Sampler(FilterType magFilter, FilterType minFilter, AddressType addressU, AddressType addressV, AddressType addressW);
		~Sampler();

		const VkSampler& GetHandle() const;

	private:
		VkSampler mHandle;
	};
}
