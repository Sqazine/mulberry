#pragma once
#include <string>
#include <string_view>
#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>
#include "Vec2.h"
#include "Logger.h"
#include "Graphics/VK/VKAdapter.h"
#include "Graphics/RasterPipeline.h"

namespace mulberry
{
	class Window
	{
	public:
		Window();
		~Window();

		void SetTitle(std::string_view str);
		std::string_view GetTitle() const;
		void Resize(const Vec2 &extent);
		void Resize(uint32_t w, uint32_t h);
		Vec2 GetSize();
		SDL_Window *GetHandle();

		const Viewport &GetViewport() const;

		void Show();
		void Hide();

	private:
		SDL_Window *mHandle;
		std::string mTitle = "";

		Viewport mViewport;

		bool mIsShown;
	private:
		friend VKAdapter;
		std::vector<const char *> GetVulkanRequiredExtensions();
		VkSurfaceKHR CreateSurface(VkInstance instance);
	};

}