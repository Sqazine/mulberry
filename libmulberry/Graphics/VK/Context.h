#pragma once
#include <cstdint>
#include <memory>
#include <vulkan/vulkan.h>
#include <mutex>
#include "Singleton.h"
#include "Graphics/GraphicsContext.h"

namespace mulberry::vk
{
	class Context : public Singleton<vk::Context>
	{
	public:
		void Init();
		void Destroy();

		class Adapter *GetAdapter() const;
		class Device *GetDevice() const;

		void BeginFrame();
		void EndFrame();
	private:
		class Adapter *mAdapter;
		class Device *mDevice;
		class SwapChain *mSwapChain;
	};
}