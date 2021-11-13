#include "PipelineCache.h"
#include <iostream>
#include "Utils.h"
PipelineCache::PipelineCache(const VkDevice &device, size_t initialDataSize, void *initialData)
    : m_TmpVKDeviceHandle(device)
{
    VkPipelineCacheCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
    info.pNext = nullptr;
    info.flags = 0;
    info.initialDataSize = initialDataSize;
    info.pInitialData = initialData;

    VK_CHECK(vkCreatePipelineCache(m_TmpVKDeviceHandle, &info, nullptr, &m_PipelineCacheHandle));
}
PipelineCache::~PipelineCache()
{
    vkDestroyPipelineCache(m_TmpVKDeviceHandle, m_PipelineCacheHandle, nullptr);
}

const VkPipelineCache &PipelineCache::GetVKPipelineCacheHandle() const
{
    return m_PipelineCacheHandle;
}