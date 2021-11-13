#pragma once
#include <vulkan/vulkan.h>
#include <string_view>
class Shader
{
public:
    Shader(const VkDevice &device, VkShaderStageFlagBits stageFlag, std::string_view filePath);
    ~Shader();

    const VkPipelineShaderStageCreateInfo &GetStageCreateInfo() const;

private:
    VkShaderModule m_ShaderModuleHandle;
    VkPipelineShaderStageCreateInfo m_StageCreateInfo;

    const VkDevice &m_TmpVKDeviceHandle;
};
