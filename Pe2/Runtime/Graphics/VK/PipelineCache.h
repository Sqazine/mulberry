#pragma once
#include <vulkan/vulkan.h>
#include <vector>
namespace Pe2::VK
{
    class PipelineCache
    {
    public:
        PipelineCache( size_t initialDataSize = 0, void *initialData = nullptr);
        ~PipelineCache();

        const VkPipelineCache &GetVKPipelineCacheHandle() const;

    private:
        VkPipelineCache m_PipelineCacheHandle;
    };
}