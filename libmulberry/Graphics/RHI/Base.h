#pragma once
#include <variant>
#include <memory>
#include "Utils.h"
namespace mulberry
{
    template <typename VkImpl>
    class Base
    {
    public:
        Base()
        {
            GRAPHICS_RHI_IMPL_SWITCHER(std::get<0>(mVkImpl) = std::make_unique<VkImpl>());
        }

        template <typename T>
        Base(const T &first)
        {
            GRAPHICS_RHI_IMPL_SWITCHER(std::get<0>(mVkImpl) = std::make_unique<VkImpl>(first));
        }

        template <typename T, typename... Args>
        Base(const T &first, Args... args)
        {
            GRAPHICS_RHI_IMPL_SWITCHER(std::get<0>(mVkImpl) = std::make_unique<VkImpl>(first, args...));
        }

        ~Base()
        {
            GRAPHICS_RHI_IMPL_SWITCHER(std::get<0>(mVkImpl).reset(nullptr));
        }

        VkImpl *GetVkImpl() const
        {
            return std::get<0>(mVkImpl).get();
        }

        std::unique_ptr<VkImpl> &GetUniVkImpl()
        {
            return std::get<0>(mVkImpl);
        }

    protected:
        std::variant<std::unique_ptr<VkImpl>> mVkImpl;
    };

#define GRAPHICS_RHI_IMPL_DECL(type) \
public                               \
    Base<vk::type>
}
