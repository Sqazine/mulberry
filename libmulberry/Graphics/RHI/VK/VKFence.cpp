#include "VKFence.h"
#include "VKDevice.h"
#include "VKContext.h"
#include "VKUtils.h"
#include "Logger.h"

namespace mulberry
{
    constexpr uint64_t FENCE_WAIT_TIME_OUT = UINT64_MAX;

    VKFence::VKFence()
    {
        VkFenceCreateInfo fenceInfo{};
        fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        VK_CHECK(vkCreateFence(VKContext::GetInstance().GetDevice()->GetHandle(), &fenceInfo, nullptr, &mHandle));
    }
    VKFence::~VKFence()
    {
        vkDestroyFence(VKContext::GetInstance().GetDevice()->GetHandle(), mHandle, nullptr);
    }

    const VkFence &VKFence::GetHandle() const
    {
        return mHandle;
    }

    void VKFence::Wait()
    {
        VK_CHECK(vkWaitForFences(VKContext::GetInstance().GetDevice()->GetHandle(), 1, &mHandle, VK_TRUE, FENCE_WAIT_TIME_OUT));
    }
    void VKFence::Reset()
    {
        VK_CHECK(vkResetFences(VKContext::GetInstance().GetDevice()->GetHandle(), 1, &mHandle));
    }
}