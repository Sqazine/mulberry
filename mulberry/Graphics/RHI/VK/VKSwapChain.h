#pragma once
#include <vector>
#include <vulkan/vulkan.h>
#include "VKImage.h"
#include "VKImageView.h"
#include "VKSyncObject.h"
namespace mulberry
{
	class VKSwapChain
	{
	public:
		VKSwapChain();
		~VKSwapChain();

		Vec2 GetExtent() const;
		uint32_t GetImageSize() const;

		const std::vector<std::unique_ptr<VKImageView>> &GetImageViews() const;
		const VkSurfaceFormatKHR GetSurfaceFormat() const;

		const VkSwapchainKHR &GetHandle() const;

		void ReBuild();

		uint32_t AcquireNextImage(const VKSemaphore *semaphore = nullptr, const VKFence *fence = nullptr) const;
	private:
		void Build();

		SwapChainDetails QuerySwapChainDetails();

		VkSurfaceFormatKHR ChooseSwapChainSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
		VkPresentModeKHR ChooseSwapChainPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
		VkExtent2D ChooseSwapChainExtent(const VkSurfaceCapabilitiesKHR &capabilities);

		VkSwapchainKHR mHandle;

		std::vector<VkImage> mSwapChainImages;
		std::vector<std::unique_ptr<VKImageView>> mSwapChainImageViews;
		VkSurfaceFormatKHR mSwapChainSurfaceFormat;
		VkExtent2D mSwapChainImageExtent;
		VkPresentModeKHR mSwapChainPresentMode;
	};
}