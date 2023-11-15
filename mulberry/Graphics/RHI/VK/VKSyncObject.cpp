#include "VKSyncObject.h"
#include <iostream>
#include "Logger.h"
#include "VKUtils.h"
#include "VKDevice.h"
#include "VKContext.h"
#include "App.h"

namespace mulberry
{
    VKFence::VKFence(FenceStatus status)
        : mHandle(VK_NULL_HANDLE), mStatus(status), mDevice(App::GetInstance().GetGraphicsContext()->GetVKContext()->GetDevice())
    {
        VkFenceCreateInfo info{};
        info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        info.pNext = nullptr;
        info.flags = mStatus == FenceStatus::SIGNALED ? VK_FENCE_CREATE_SIGNALED_BIT : 0;

        VK_CHECK(vkCreateFence(mDevice->GetHandle(), &info, nullptr, &mHandle));
    }
    VKFence::~VKFence()
    {
        Wait();
        Reset();
        vkDestroyFence(mDevice->GetHandle(), mHandle, nullptr);
        mDevice = nullptr;
    }

    const VkFence &VKFence::GetHandle() const
    {
        return mHandle;
    }

    void VKFence::Wait(bool waitAll, uint64_t timeout)
    {
        VK_CHECK(vkWaitForFences(mDevice->GetHandle(), 1, &mHandle, waitAll, timeout));
    }

    void VKFence::Reset()
    {
        VK_CHECK(vkResetFences(mDevice->GetHandle(), 1, &mHandle));
    }

    FenceStatus VKFence::GetStatus() const
    {
        return mStatus;
    }

    VKSemaphore::VKSemaphore()
        : mHandle(VK_NULL_HANDLE), mDevice(App::GetInstance().GetGraphicsContext()->GetVKContext()->GetDevice())
    {
        VkSemaphoreCreateInfo info = {};
        info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
        info.pNext = nullptr;
        info.flags = 0;

        VK_CHECK(vkCreateSemaphore(mDevice->GetHandle(), &info, nullptr, &mHandle));
    }
    VKSemaphore::~VKSemaphore()
    {
        vkDestroySemaphore(mDevice->GetHandle(), mHandle, nullptr);
        mDevice = nullptr;
    }

    const VkSemaphore &VKSemaphore::GetHandle() const
    {
        return mHandle;
    }
}