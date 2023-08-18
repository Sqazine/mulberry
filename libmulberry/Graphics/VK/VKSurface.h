#pragma once
#include <vulkan/vulkan.h>

namespace mulberry
{
    class VKSurface 
    {
    public:
        VKSurface();
        ~VKSurface();

      const  VkSurfaceKHR& GetHandle() const;

    private:
        VkSurfaceKHR mSurfaceHandle;
    };
}