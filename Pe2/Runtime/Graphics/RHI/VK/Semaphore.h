#pragma once
#include <vulkan/vulkan.h>
class Semaphore
{
public:
    Semaphore(const VkDevice &device);
    ~Semaphore();

    const VkSemaphore &GetVKSemaphoreHandle() const;

private:
    VkSemaphore m_SemaphoreHandle;
    const VkDevice &m_TmpVkDevice;
};