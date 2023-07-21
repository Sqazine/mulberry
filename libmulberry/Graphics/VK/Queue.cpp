#include "Queue.h"
#include "Device.h"
#include "Logger.h"
#include "Utils.h"
#include "Context.h"
namespace mulberry::vk
{
	Queue::Queue(uint32_t familyIndex)
	{
		vkGetDeviceQueue(Context::GetInstance().GetDevice()->GetHandle(), familyIndex, 0, &mHandle);
	}

	void Queue::WaitIdle() const
	{
		VK_CHECK(vkQueueWaitIdle(mHandle))
	}

	const VkQueue &Queue::GetHandle() const
	{
		return mHandle;
	}

	GraphicsQueue::GraphicsQueue(uint32_t familyIndex)
		: Queue(familyIndex)
	{
	}

	void GraphicsQueue::Submit(const VkSubmitInfo &submitInfo, const Fence *fence) const
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

	void PresentQueue::Present(const VkPresentInfoKHR &info) const
	{
		VK_CHECK(vkQueuePresentKHR(mHandle, &info))
	}
}