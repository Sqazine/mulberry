#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include "Utils.h"
#include "SyncObject.h"
#include "Math/Vec2.h"
namespace mulberry::vk
{
	class SwapChain:public Object
	{
	public:
		SwapChain();
		~SwapChain();

		Vec2 GetExtent() const;

		std::vector<class Texture*>& GetTextures();
		const VkSurfaceFormatKHR GetSurfaceFormat() const;

		const VkSwapchainKHR &GetHandle() const;

		void ReBuild();

		void AcquireNextImage(const Semaphore *semaphore = nullptr, const Fence *fence = nullptr);
		uint32_t GetNextImageIdx() const;

		void Present(const Semaphore *waitSemaphore);

	private:
		void Build();

		SwapChainDetails QuerySwapChainDetails();

		VkSurfaceFormatKHR ChooseSwapChainSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
		VkPresentModeKHR ChooseSwapChainPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
		VkExtent2D ChooseSwapChainExtent(const VkSurfaceCapabilitiesKHR &capabilities);

		void DeleteImageViews();

		VkSwapchainKHR mHandle;

		std::vector<class Texture*> mSwapChainTextures;

		VkSurfaceFormatKHR mSwapChainSurfaceFormat;
		VkExtent2D mSwapChainImageExtent;
		VkPresentModeKHR mSwapChainPresentMode;

		uint32_t mNextImageIdx;
	};
}