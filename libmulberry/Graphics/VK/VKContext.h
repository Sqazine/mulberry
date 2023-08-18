#pragma once
#include <cstdint>
#include <memory>
#include <vulkan/vulkan.h>
#include <mutex>
#include "Singleton.h"
#include "Graphics/GraphicsContext.h"

namespace mulberry
{
	class VKContext : public Singleton<VKContext>
	{
	public:
		void Init();
		void Destroy();

		class VKAdapter *GetAdapter() const;
		class VKDevice *GetDevice() const;

		void BeginFrame();
		void EndFrame();
	private:
		class VKAdapter *mAdapter;
		class VKDevice *mDevice;
		class VKSwapChain *mSwapChain;
	};
}