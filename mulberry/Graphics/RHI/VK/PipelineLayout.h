#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include "Object.h"
#include "Descriptor.h"

namespace mulberry::vk
{

	class PipelineLayout : public Object
	{
	public:
		PipelineLayout();
		~PipelineLayout();

		PipelineLayout &AddDescriptorSetLayout(DescriptorSetLayout *descriptorSetLayout);
		PipelineLayout &SetDescriptorSetLayouts(const std::vector<DescriptorSetLayout *> &descriptorSetLayouts);

		const VkPipelineLayout &GetHandle();

	private:
		void Build();

		std::vector<DescriptorSetLayout *> mDescriptorSetLayoutCache;

		VkPipelineLayout mHandle;
	};
}