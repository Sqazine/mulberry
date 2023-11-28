#pragma once
#include <string>
#include <string_view>
#include <SDL.h>
#include <SDL_vulkan.h>
#include "Vec2.h"
#include "Logger.h"
#include "Graphics/RHI/VK/VKAdapter.h"
#include "Graphics/RHI/RasterPipeline.h"
#include "Platform/Window.h"
namespace mulberry
{
	class SDL2WindowImpl : public Window
	{
	public:
		SDL2WindowImpl();
		~SDL2WindowImpl() override;

		void SetTitle(std::string_view str) override;
		std::string_view GetTitle() const override;
		void Resize(const Vec2 &extent) override;
		void Resize(uint32_t w, uint32_t h) override;
		Vec2 GetSize() override;
		SDL_Window *GetHandle();

		const Viewport &GetViewport() const override;

		void Show() override;
		void Hide() override;

		bool IsWindowCloseButtonClick() const override;
		bool IsWindowMaxButtonClick() const override;
		bool IsWindowMinButtonClick() const override;

		bool IsResize() const override;
	private:
		SDL_Window *mHandle;
		std::string mTitle = "";

		Viewport mViewport;

		bool mIsShown;

		bool mIsWindowCloseButtonClick;
		bool mIsWindowMaxButtonClick;
		bool mIsWindowMinButtonClick;
		bool mIsWindowResize;

	protected:
		void PreUpdate() override;
		void PostUpdate() override;
		std::vector<const char *> GetVulkanRequiredExtensions() override;
		VkSurfaceKHR CreateSurface(VkInstance instance) override;
	};

}