#pragma once
#include <vulkan/vulkan.h>
#include <vector>
class PipelineCache
{
public:
    PipelineCache(const VkDevice &device, size_t initialDataSize=0, void* initialData = nullptr);
    ~PipelineCache();

    const VkPipelineCache &GetVKPipelineCacheHandle() const;

private:
    VkPipelineCache m_PipelineCacheHandle;
    const VkDevice &m_TmpVKDeviceHandle;
};