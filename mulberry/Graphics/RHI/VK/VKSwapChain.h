#pragma once
#include <vector>
#include <vulkan/vulkan.h>
#include "VKImage.h"
#include "VKSyncObject.h"
#include "VKTexture.h"
namespace mulberry
{
	class VKSwapChain
	{
	public:
		VKSwapChain();
		~VKSwapChain();

		Vec2 GetExtent() const;

		const std::vector<std::vector<const VKTexture*>>& GetTextures() const;
		const VkSurfaceFormatKHR GetSurfaceFormat() const;

		const VkSwapchainKHR &GetHandle() const;

		void ReBuild();

		void AcquireNextImage(const VKSemaphore *semaphore = nullptr, const VKFence *fence = nullptr);
		uint32_t GetNextImageIdx() const;

		void Present(const VKSemaphore *waitSemaphore);

	private:
		void Build();

		SwapChainDetails QuerySwapChainDetails();

		VkSurfaceFormatKHR ChooseSwapChainSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
		VkPresentModeKHR ChooseSwapChainPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
		VkExtent2D ChooseSwapChainExtent(const VkSurfaceCapabilitiesKHR &capabilities);

		void DeleteImageViews();

		VkSwapchainKHR mHandle;

		std::vector<std::vector<const VKTexture*>> mSwapChainTextures;

		VkSurfaceFormatKHR mSwapChainSurfaceFormat;
		VkExtent2D mSwapChainImageExtent;
		VkPresentModeKHR mSwapChainPresentMode;

		uint32_t mNextImageIdx;
	};
}