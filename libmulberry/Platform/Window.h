#pragma once
#include <vulkan/vulkan.h>
#include <cstdint>
#include <string_view>
#include <vector>
#include "Math/Vec2.h"
#include "Graphics/RHI/Viewport.h"

namespace mulberry
{
    class Window
    {
    public:
        enum Event : uint32_t
        {
            NONE = 0,
            MIN = 1,
            MAX = 2,
            RESTORE = 4,
            CLOSE = 8,
            RESIZE = 16,
            MOVE = 32,
            ENTER = 64,
            LEAVE = 128,
            EXPOSE = 256,
        };

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

        virtual std::vector<const char *> GetVulkanRequiredExtensions() = 0;
        virtual VkSurfaceKHR CreateSurface(VkInstance instance) = 0;

        virtual void SetEvent(Event event)
        {
            mEvent = Event((uint32_t)mEvent | (uint32_t)event);
        }

        virtual Event GetEvent() const
        {
            return mEvent;
        }

        virtual bool HasEvent(Event event)
        {
            return (mEvent & event) == event;
        }

        virtual bool HasEvent(uint32_t event)
        {
            return (mEvent & (Event)event) != Event::NONE;
        }

        virtual void ClearEvent()
        {
            mEvent = Event::NONE;
        }

    protected:
        Event mEvent{Event::NONE};
    };
}