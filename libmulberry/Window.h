#pragma once
#include <string>
#include <string_view>
#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>
#include "Vec2.h"
#include "Logger.h"
#include "Graphics/VK/Adapter.h"

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

		const std::array<int32_t,4>& GetViewportInfo() const;

		void Show();
		void Hide();
	private:
		SDL_Window *mHandle;
		std::string mTitle = "";

		std::array<int32_t,4> mViewportInfo;

		bool mIsShown;
	private:
		friend vk::Adapter;
		std::vector<const char *> GetVulkanRequiredExtensions();
		VkSurfaceKHR CreateSurface(VkInstance instance);
	};

}