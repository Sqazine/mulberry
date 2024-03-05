#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <memory>
#include "Utils.h"
#include "SyncObject.h"
#include "Math/Vec2.h"
namespace mulberry::rhi::vk
{
	class SwapChain:public Base
	{
	public:
		SwapChain();
		~SwapChain();

		Vec2 GetExtent() const;

		std::vector<class Texture *> &GetTextures();
		const VkSurfaceFormatKHR GetSurfaceFormat() const;

		const VkSwapchainKHR &GetHandle() const;

		class FrameBuffer *GetCurrentDefaultFrameBuffer() const;
		class RenderPass* GetDefaultRenderPass() const;

		void ReBuild();

		void AcquireNextImage(const Semaphore *semaphore = nullptr, const Fence *fence = nullptr);
		uint32_t GetNextImageIdx() const;

		VkResult Present(const Semaphore *waitSemaphore);

	private:
		void Build();

		SwapChainDetails QuerySwapChainDetails();

		VkSurfaceFormatKHR ChooseSwapChainSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);
		VkPresentModeKHR ChooseSwapChainPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);
		VkExtent2D ChooseSwapChainExtent(const VkSurfaceCapabilitiesKHR &capabilities);

		void DeleteImageViews();

		VkSwapchainKHR mHandle;

		std::vector<class Texture *> mSwapChainTextures;

		std::unique_ptr<class RenderPass> mDefaultRenderPass;
		std::vector<std::unique_ptr<class FrameBuffer>> mDefaultFrameBuffers;

		VkSurfaceFormatKHR mSwapChainSurfaceFormat;
		VkExtent2D mSwapChainImageExtent;
		VkPresentModeKHR mSwapChainPresentMode;

		uint32_t mNextImageIdx;
	};
}