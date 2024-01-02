#pragma once
#include <cstdint>
#include <memory>
#include <vulkan/vulkan.h>
#include <mutex>
#include <vector>
#include "Math/Color.h"
#include "RasterPass.h"

namespace mulberry::vk
{
	class Context
	{
	public:
		Context();
		~Context();

		void Init();

		class Adapter *GetAdapter() const;
		class Device *GetDevice() const;
		class SwapChain *GetSwapChain() const;

		void SetClearColor(const Color &clearColor);
		void IsClearColorBuffer(bool isClear);

		void BeginFrame();
		void EndFrame();

		const RasterPass* GetCurRasterPass() const;

		size_t GetCurFrameIdx() const;

	private:

		friend class RasterPass;

		const RasterPass* mCurRasterPass;

		size_t mCurFrameIdx = 0;

		std::unique_ptr<class Adapter >mAdapter;
		std::unique_ptr<class Device >mDevice;
		std::unique_ptr<class SwapChain >mSwapChain;

		std::unique_ptr<class RasterPass> mDefaultRasterPass;
	};
}