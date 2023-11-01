#pragma once
#include <cstdint>
#include <memory>
#include <vulkan/vulkan.h>
#include <mutex>
#include <vector>
#include "Math/Color.h"

namespace mulberry
{
	class VKContext
	{
	public:
		VKContext();
		~VKContext();

		void Init();

		class VKAdapter *GetAdapter() const;
		class VKDevice *GetDevice() const;
		class VKSwapChain *GetSwapChain() const;

		void SetClearColor(const Color &clearColor);
		void IsClearColorBuffer(bool isClear);

		void BeginFrame();
		void EndFrame();

	private:
		std::unique_ptr<class VKAdapter >mAdapter;
		std::unique_ptr<class VKDevice >mDevice;
		std::unique_ptr<class VKSwapChain >mSwapChain;

		std::unique_ptr<class VKDrawPass> mDefaultDrawPass;
	};
}