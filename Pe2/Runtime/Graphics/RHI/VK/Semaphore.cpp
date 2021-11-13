#include "Semaphore.h"
#include <iostream>
#include "Utils.h"
Semaphore::Semaphore(const VkDevice &device)
    : m_TmpVkDevice(device)
{
    VkSemaphoreCreateInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    info.pNext = nullptr;
    info.flags = 0;

    VK_CHECK(vkCreateSemaphore(m_TmpVkDevice, &info, nullptr, &m_SemaphoreHandle));
}
Semaphore::~Semaphore()
{
    vkDestroySemaphore(m_TmpVkDevice, m_SemaphoreHandle, nullptr);
}

const VkSemaphore &Semaphore::GetVKSemaphoreHandle() const
{
    return m_SemaphoreHandle;
}