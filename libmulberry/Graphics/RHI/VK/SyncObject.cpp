#include "SyncObject.h"
#include <iostream>
#include "Logger.h"
#include "Utils.h"
#include "Device.h"

namespace mulberry::vk
{
    Fence::Fence(FenceStatus status)
        : mHandle(VK_NULL_HANDLE), mStatus(status)
    {
        VkFenceCreateInfo info{};
        info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        info.pNext = nullptr;
        info.flags = mStatus == FenceStatus::SIGNALED ? VK_FENCE_CREATE_SIGNALED_BIT : 0;

        VK_CHECK(vkCreateFence(mDevice.GetHandle(), &info, nullptr, &mHandle));
    }

    Fence::~Fence()
    {
        Wait();
        Reset();
        vkDestroyFence(mDevice.GetHandle(), mHandle, nullptr);
    }

    const VkFence &Fence::GetHandle() const
    {
        return mHandle;
    }

    void Fence::Wait(bool waitAll, uint64_t timeout)
    {
        VK_CHECK(vkWaitForFences(mDevice.GetHandle(), 1, &mHandle, waitAll, timeout));
    }

    void Fence::Reset()
    {
        VK_CHECK(vkResetFences(mDevice.GetHandle(), 1, &mHandle));
    }

    FenceStatus Fence::GetStatus() const
    {
        return mStatus;
    }

    Semaphore::Semaphore()
        : mHandle(VK_NULL_HANDLE)
    {
        VkSemaphoreCreateInfo info = {};
        info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
        info.pNext = nullptr;
        info.flags = 0;

        VK_CHECK(vkCreateSemaphore(mDevice.GetHandle(), &info, nullptr, &mHandle));
    }
    Semaphore::~Semaphore()
    {
        vkDestroySemaphore(mDevice.GetHandle(), mHandle, nullptr);
    }

    const VkSemaphore &Semaphore::GetHandle() const
    {
        return mHandle;
    }
}