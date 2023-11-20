#include "VKQueue.h"
#include "VKDevice.h"
#include "Logger.h"
#include "VKUtils.h"
#include "VKContext.h"
#include "App.h"
namespace mulberry
{
	VKQueue::VKQueue(uint32_t familyIndex)
	{
		vkGetDeviceQueue(RAW_VK_DEVICE_HANDLE, familyIndex, 0, &mHandle);
	}

	void VKQueue::WaitIdle() const
	{
		VK_CHECK(vkQueueWaitIdle(mHandle))
	}

	const VkQueue &VKQueue::GetHandle() const
	{
		return mHandle;
	}

	VKGraphicsQueue::VKGraphicsQueue(uint32_t familyIndex)
		: VKQueue(familyIndex)
	{
	}

	void VKGraphicsQueue::Submit(const VkSubmitInfo &submitInfo, const VKFence *fence) const
	{
		if (fence)
			VK_CHECK(vkQueueSubmit(mHandle, 1, &submitInfo, fence->GetHandle()))
		else
			VK_CHECK(vkQueueSubmit(mHandle, 1, &submitInfo, VK_NULL_HANDLE))
	}

	VKPresentQueue::VKPresentQueue(uint32_t familyIndex)
		: VKQueue(familyIndex)
	{
	}

	void VKPresentQueue::Present(const VkPresentInfoKHR &info) const
	{
		VK_CHECK(vkQueuePresentKHR(mHandle, &info))
	}
}