#include "VKSampler.h"
#include "VKContext.h"
#include "Logger.h"
#include "VKDevice.h"
#include "VKUtils.h"

namespace mulberry {

	VKSampler::VKSampler(FilterType magFilter, FilterType minFilter, AddressType addressU, AddressType addressV, AddressType addressW)
	{
		VkSamplerCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
		createInfo.magFilter = (VkFilter)magFilter;
		createInfo.minFilter = (VkFilter)minFilter;
		createInfo.addressModeU = (VkSamplerAddressMode)addressU;
		createInfo.addressModeV = (VkSamplerAddressMode)addressV;
		createInfo.addressModeW = (VkSamplerAddressMode)addressW;

		VK_CHECK(vkCreateSampler(VKContext::GetInstance().GetDevice()->GetHandle(), &createInfo, nullptr, &mHandle));
	}
	VKSampler::~VKSampler()
	{
		vkDestroySampler(VKContext::GetInstance().GetDevice()->GetHandle(), mHandle, nullptr);
	}

	const VkSampler& VKSampler::GetHandle() const
	{
		return mHandle;
	}
}