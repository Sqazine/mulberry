#include "Queue.h"
#include "Device.h"
#include "Logger.h"
#include "Utils.h"

namespace mulberry::rhi::vk
{
	Queue::Queue(uint32_t familyIndex)
	{
		vkGetDeviceQueue(mDevice.GetHandle(), familyIndex, 0, &mHandle);
	}

	Queue::~Queue()
	{
	}

	void Queue::WaitIdle() const
	{
		VK_CHECK(vkQueueWaitIdle(mHandle))
	}

	const VkQueue &Queue::GetHandle() const
	{
		return mHandle;
	}

	RasterQueue::RasterQueue(uint32_t familyIndex)
		: Queue(familyIndex)
	{
	}

	RasterQueue::~RasterQueue()
	{
	}

	void RasterQueue::Submit(const VkSubmitInfo &submitInfo, const Fence *fence) const
	{
		if (fence)
			VK_CHECK(vkQueueSubmit(mHandle, 1, &submitInfo, fence->GetHandle()))
		else
			VK_CHECK(vkQueueSubmit(mHandle, 1, &submitInfo, VK_NULL_HANDLE))
	}

	PresentQueue::PresentQueue(uint32_t familyIndex)
		: Queue(familyIndex)
	{
	}

	PresentQueue::~PresentQueue()
	{
	}

	VkResult PresentQueue::Present(const VkPresentInfoKHR &info) const
	{
		return vkQueuePresentKHR(mHandle, &info);
	}
}