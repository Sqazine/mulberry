#include "Fence.h"
#include "Logger.h"
#include "Device.h"
#include "Context.h"
#include "Utils.h"

namespace mulberry::vk
{
    Fence::Fence()
    {
        VkFenceCreateInfo fenceInfo{};
        fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        VK_CHECK(vkCreateFence(Context::GetInstance().GetDevice()->GetHandle(), &fenceInfo, nullptr, &mHandle));
    }
    Fence::~Fence()
    {
        vkDestroyFence(Context::GetInstance().GetDevice()->GetHandle(), mHandle, nullptr);
    }

    const VkFence &Fence::GetHandle() const
    {
        return mHandle;
    }

    void Fence::Wait()
    {
        VK_CHECK(vkWaitForFences(Context::GetInstance().GetDevice()->GetHandle(), 1, &mHandle, VK_TRUE, FENCE_WAIT_TIME_OUT));
    }
    void Fence::Reset()
    {
        VK_CHECK(vkResetFences(Context::GetInstance().GetDevice()->GetHandle(), 1, &mHandle));
    }
}