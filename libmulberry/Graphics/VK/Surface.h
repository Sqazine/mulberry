#pragma once
#include <vulkan/vulkan.h>

namespace mulberry::vk
{
    class Surface 
    {
    public:
        Surface();
        ~Surface();

      const  VkSurfaceKHR& GetHandle() const;

    private:
        VkSurfaceKHR mSurfaceHandle;
    };
}