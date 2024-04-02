#pragma once
#include <cstdint>
#include <memory>
#include <vulkan/vulkan.h>
#include <mutex>
#include <vector>
#include "Color.h"
#include "Pass.h"

namespace mulberry::vk
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
	private:

		std::unique_ptr<class Adapter> mAdapter;
		std::unique_ptr<class Device> mDevice;
	};
}