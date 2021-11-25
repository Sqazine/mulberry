#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Utils.h"
#include "Context.h"
namespace VK
{
    Shader::Shader( VkShaderStageFlagBits stageFlag, std::string_view spvContent)   
    {
        VkShaderModuleCreateInfo info;
        info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        info.flags = 0;
        info.pNext = nullptr;
        info.codeSize = spvContent.size();
        info.pCode = reinterpret_cast<const uint32_t *>(spvContent.data());

        VK_CHECK(vkCreateShaderModule(Context::GetDevice()->GetLogicalDeviceHandle(), &info, nullptr, &m_ShaderModuleHandle));

        m_StageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        m_StageCreateInfo.pNext = nullptr;
        m_StageCreateInfo.flags = 0;
        m_StageCreateInfo.stage = stageFlag;
        m_StageCreateInfo.module = m_ShaderModuleHandle;
        m_StageCreateInfo.pName = "main";
        m_StageCreateInfo.pSpecializationInfo = nullptr;
    }
    Shader::~Shader()
    {
        vkDestroyShaderModule(Context::GetDevice()->GetLogicalDeviceHandle(), m_ShaderModuleHandle, nullptr);
    }

    const VkPipelineShaderStageCreateInfo &Shader::GetStageCreateInfo() const
    {
        return m_StageCreateInfo;
    }

}