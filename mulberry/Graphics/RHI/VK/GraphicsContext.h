#pragma once
#include <cstdint>
#include <memory>
#include <vulkan/vulkan.h>
#include <mutex>
#include <vector>
#include "Color.h"
#include "RasterPass.h"

namespace mulberry::rhi::vk
{
	class GraphicsContext
	{
	public:
		GraphicsContext();
		~GraphicsContext();

		void Init();

		class Adapter *GetAdapter() const;
		class Device *GetDevice() const;
		class SwapChain *GetSwapChain() const;

		void SetClearColor(const Color &clearColor);
		void IsClearColorBuffer(bool isClear);

		void BeginFrame();
		void EndFrame();

		const RasterPass *GetDefaultRasterPass() const;

		size_t GetCurFrameIdx() const;

	private:
		friend class RasterPass;

		size_t mCurFrameIdx = 0;

		std::unique_ptr<class Adapter> mAdapter;
		std::unique_ptr<class Device> mDevice;
		std::unique_ptr<class SwapChain> mSwapChain;

		std::unique_ptr<class RasterPass> mDefaultRasterPass;
	};
}