#pragma once
#include <cstdint>
#include <memory>
#include <vulkan/vulkan.h>
#include <mutex>
#include <vector>
#include "Color.h"
#include "Pass.h"

namespace mulberry::rhi::vk
{
	class GraphicsContext
	{
	public:
		GraphicsContext();
		~GraphicsContext();

		void Init();
		void Destroy();

		class Adapter *GetAdapter() const;
		class Device *GetDevice() const;
		class SwapChain *GetSwapChain() const;

		void BeginFrame();
		void EndFrame();

		size_t GetCurFrameIdx() const;

	private:
		friend class GraphicsPass;

		size_t mCurFrameIdx = 0;

		std::unique_ptr<class Adapter> mAdapter;
		std::unique_ptr<class Device> mDevice;
		std::unique_ptr<class SwapChain> mSwapChain;
	};
}