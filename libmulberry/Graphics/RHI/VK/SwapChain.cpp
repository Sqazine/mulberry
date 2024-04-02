#include "SwapChain.h"
#include <SDL.h>
#include <algorithm>
#include "Device.h"
#include "Utils.h"
#include "Logger.h"
#include "Texture.h"
#include "RenderPass.h"
#include "FrameBuffer.h"
#include "App.h"
#include "AppConfig.h"
#include "GraphicsContext.h"
namespace mulberry::vk
{
	SwapChain::SwapChain()
		: mHandle(VK_NULL_HANDLE), mNextImageIdx(0)
	{
		Build();
	}

	SwapChain::~SwapChain()
	{
		DeleteImageViews();

		vkDestroySwapchainKHR(mDevice.GetHandle(), mHandle, nullptr);
	}

	std::vector<Texture *> &SwapChain::GetTextures()
	{
		return mBackTextures;
	}

	const VkSurfaceFormatKHR SwapChain::GetSurfaceFormat() const
	{
		return mSurfaceFormat;
	}

	Vec2 SwapChain::GetExtent() const
	{
		return Vec2(mExtent.width, mExtent.height);
	}

	void SwapChain::AcquireNextImage(const Semaphore *semaphore, const Fence *fence)
	{
		if (semaphore && fence)
			VK_CHECK(vkAcquireNextImageKHR(mDevice.GetHandle(), mHandle, UINT64_MAX, semaphore->GetHandle(), fence->GetHandle(), &mNextImageIdx))
		else if (semaphore && !fence)
			VK_CHECK(vkAcquireNextImageKHR(mDevice.GetHandle(), mHandle, UINT64_MAX, semaphore->GetHandle(), nullptr, &mNextImageIdx))
		else if (!semaphore && fence)
			VK_CHECK(vkAcquireNextImageKHR(mDevice.GetHandle(), mHandle, UINT64_MAX, nullptr, fence->GetHandle(), &mNextImageIdx))
		else
			VK_CHECK(vkAcquireNextImageKHR(mDevice.GetHandle(), mHandle, UINT64_MAX, nullptr, nullptr, &mNextImageIdx))
	}

	uint32_t SwapChain::GetNextImageIdx() const
	{
		return mNextImageIdx;
	}

	VkResult SwapChain::Present(const Semaphore *waitSemaphore)
	{
		VkPresentInfoKHR presentInfo{};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = &mHandle;
		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = &waitSemaphore->GetHandle();
		presentInfo.pImageIndices = &mNextImageIdx;

		return mDevice.GetPresentQueue()->Present(presentInfo);
	}

	void SwapChain::Build()
	{
		SwapChainDetails swapChainDetail = QuerySwapChainDetails();
		mSurfaceFormat = ChooseSwapChainSurfaceFormat(swapChainDetail.surfaceFormats);
		mPresentMode = ChooseSwapChainPresentMode(swapChainDetail.presentModes);
		mExtent = ChooseSwapChainExtent(swapChainDetail.surfaceCapabilities);

		uint32_t imageCount = swapChainDetail.surfaceCapabilities.minImageCount;
		if (swapChainDetail.surfaceCapabilities.maxImageCount > 0 && imageCount > swapChainDetail.surfaceCapabilities.maxImageCount)
			imageCount = swapChainDetail.surfaceCapabilities.maxImageCount;

		VkSwapchainCreateInfoKHR createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.pNext = nullptr;
		createInfo.flags = 0;
		createInfo.surface = VK_CONTEXT->GetAdapter()->GetSurface();
		createInfo.minImageCount = imageCount;
		createInfo.imageFormat = mSurfaceFormat.format;
		createInfo.imageColorSpace = mSurfaceFormat.colorSpace;
		createInfo.imageExtent = mExtent;
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		QueueFamilyIndices indices = mDevice.GetPhysicalDeviceSpec().queueFamilyIndices;
		if (indices.graphicsFamilyIdx.value() != indices.presentFamilyIdx.value())
		{
			uint32_t queueFamilyIndices[] = {indices.graphicsFamilyIdx.value(), indices.presentFamilyIdx.value()};
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = queueFamilyIndices;
		}
		else
		{
			createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			createInfo.queueFamilyIndexCount = 0;
			createInfo.pQueueFamilyIndices = nullptr;
		}

		createInfo.preTransform = swapChainDetail.surfaceCapabilities.currentTransform;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = mPresentMode;
		createInfo.oldSwapchain = mHandle == VK_NULL_HANDLE ? mHandle : VK_NULL_HANDLE;

		VK_CHECK(vkCreateSwapchainKHR(mDevice.GetHandle(), &createInfo, nullptr, &mHandle));

		uint32_t count = 0;
		vkGetSwapchainImagesKHR(mDevice.GetHandle(), mHandle, &count, nullptr);
		std::vector<VkImage> rawImages(count);
		vkGetSwapchainImagesKHR(mDevice.GetHandle(), mHandle, &count, rawImages.data());

		mBackTextures.resize(count);
		for (size_t i = 0; i < rawImages.size(); ++i)
			mBackTextures[i] = new Texture(GetExtent(), rawImages[i], mSurfaceFormat.format);
	}

	const VkSwapchainKHR &SwapChain::GetHandle() const
	{
		return mHandle;
	}

	void SwapChain::SyncToWindowSize()
	{
		VK_CONTEXT->GetDevice()->WaitIdle();

		DeleteImageViews();
		vkDestroySwapchainKHR(mDevice.GetHandle(), mHandle, nullptr);
		Build();
	}

	VkSurfaceFormatKHR SwapChain::ChooseSwapChainSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats)
	{
		for (const auto &availableFormat : availableFormats)
			if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
				return availableFormat;
		return availableFormats[0];
	}

	VkPresentModeKHR SwapChain::ChooseSwapChainPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes)
	{
		for (const auto &availablePresentMode : availablePresentModes)
			if (AppConfig::graphicsConfig.useVSync && availablePresentMode == VK_PRESENT_MODE_FIFO_KHR)
				return availablePresentMode;

		for (const auto &availablePresentMode : availablePresentModes)
			if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
				return availablePresentMode;

		return VK_PRESENT_MODE_IMMEDIATE_KHR;
	}

	VkExtent2D SwapChain::ChooseSwapChainExtent(const VkSurfaceCapabilitiesKHR &capabilities)
	{
		if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max() && capabilities.currentExtent.height != std::numeric_limits<uint32_t>::max())
			return capabilities.currentExtent;
		else
		{
			auto size = App::GetInstance().GetWindow()->GetSize();
			VkExtent2D actualExtent =
				{
					(uint32_t)size.x,
					(uint32_t)size.y,
				};

			actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
			actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

			return actualExtent;
		}
	}

	void SwapChain::DeleteImageViews()
	{
		for (size_t i = 0; i < mBackTextures.size(); ++i)
		{
			delete mBackTextures[i];
			mBackTextures[i] = nullptr;
		}

		std::vector<Texture *>().swap(mBackTextures);
	}

	SwapChainDetails SwapChain::QuerySwapChainDetails()
	{
		SwapChainDetails result;

		auto surface = VK_CONTEXT->GetAdapter()->GetSurface();
		auto physicalDevice = VK_CONTEXT->GetDevice()->GetPhysicalDeviceSpec().handle;

		uint32_t count = 0;
		vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &count, nullptr);
		result.surfaceFormats.resize(count);
		vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &count, result.surfaceFormats.data());

		count = 0;
		vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &count, nullptr);
		result.presentModes.resize(count);
		vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &count, result.presentModes.data());

		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &result.surfaceCapabilities);

		return result;
	}
}