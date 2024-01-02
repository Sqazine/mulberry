#pragma once
#include <vulkan/vulkan.h>
#include <cstdint>
#include <string_view>
#include "Math/Vec2.h"
#include "Graphics/RHI/Pipeline.h"
#include "Graphics/Viewport.h"

namespace mulberry
{
    class Window
    {
    public:
        Window() = default;
        virtual ~Window() = default;

        virtual void SetTitle(std::string_view str) = 0;
        virtual std::string_view GetTitle() const = 0;
        virtual void Resize(const Vec2 &extent) = 0;
        virtual void Resize(uint32_t w, uint32_t h) = 0;
        virtual Vec2 GetSize() = 0;

        virtual const Viewport &GetViewport() const = 0;

        virtual void Show() = 0;
        virtual void Hide() = 0;

        virtual bool IsWindowCloseButtonClick() const = 0;
        virtual bool IsWindowMaxButtonClick() const = 0;
        virtual bool IsWindowMinButtonClick() const = 0;

        virtual bool IsResize() const = 0;

		virtual std::vector<const char*> GetVulkanRequiredExtensions() = 0;
		virtual VkSurfaceKHR CreateSurface(VkInstance instance) = 0;
    protected:
        friend class App;
        virtual void PreUpdate() = 0;
        virtual void PostUpdate() = 0;

    };
}