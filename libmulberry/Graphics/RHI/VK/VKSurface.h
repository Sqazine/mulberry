#pragma once
#include <vulkan/vulkan.h>

namespace mulberry
{
    class VKSurface 
    {
    public:
        VKSurface(const VkInstance& instance);
        ~VKSurface();

      const  VkSurfaceKHR& GetHandle() const;

    private:
        const VkInstance& mInstanceHandle;
        VkSurfaceKHR mSurfaceHandle;
    };
}