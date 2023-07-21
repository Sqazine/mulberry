#include "Sampler.h"
#include "Context.h"
#include "Logger.h"
#include "Device.h"
#include "Utils.h"

namespace mulberry::vk {

	Sampler::Sampler(FilterType magFilter, FilterType minFilter, AddressType addressU, AddressType addressV, AddressType addressW)
	{
		VkSamplerCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
		createInfo.magFilter = (VkFilter)magFilter;
		createInfo.minFilter = (VkFilter)minFilter;
		createInfo.addressModeU = (VkSamplerAddressMode)addressU;
		createInfo.addressModeV = (VkSamplerAddressMode)addressV;
		createInfo.addressModeW = (VkSamplerAddressMode)addressW;

		VK_CHECK(vkCreateSampler(Context::GetInstance().GetDevice()->GetHandle(), &createInfo, nullptr, &mHandle));
	}
	Sampler::~Sampler()
	{
		vkDestroySampler(Context::GetInstance().GetDevice()->GetHandle(), mHandle, nullptr);
	}

	const VkSampler& Sampler::GetHandle() const
	{
		return mHandle;
	}
}