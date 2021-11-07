#pragma once
#include <vulkan/vulkan.h>
#include <string_view>

namespace VK
{
    enum ShaderModuleType
    {
        VERTEX_SHADER = VK_SHADER_STAGE_VERTEX_BIT,
        FRAGMENT_SHADER = VK_SHADER_STAGE_FRAGMENT_BIT,
        GEOMETRY_SHADER = VK_SHADER_STAGE_GEOMETRY_BIT,
        TESSELLATION_CONTROL_SHADER = VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT,
        TESSELLATION_EVAL_SHADER = VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT,
        COMPUTE_SHADER = VK_SHADER_STAGE_COMPUTE_BIT,
        MESH_SHADER = VK_SHADER_STAGE_MESH_BIT_NV, //only for nvidia turning+ card
        TASK_SHADER = VK_SHADER_STAGE_TASK_BIT_NV, //only for nvidia turning+ card
        RAY_GEN_SHADER = VK_SHADER_STAGE_RAYGEN_BIT_KHR,
        RAY_ANY_HIT_SHADER = VK_SHADER_STAGE_ANY_HIT_BIT_KHR,
        RAY_CLOSTEST_HIT_SHADER = VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR,
        RAY_MISS_SHADER = VK_SHADER_STAGE_MISS_BIT_KHR,
        RAY_INTERSECTION_SHADER = VK_SHADER_STAGE_INTERSECTION_BIT_KHR,
        RAY_CALLABLE_SHADER = VK_SHADER_STAGE_CALLABLE_BIT_KHR,
    };

    class ShaderModule
    {
    public:
        ShaderModule();
        ~ShaderModule();
        

        bool CompileSource(const ShaderModuleType &type, std::string_view content);
        bool CompileBinary(const ShaderModuleType &type, std::string_view content);

        const ShaderModuleType &Type() const;

    private:
        ShaderModuleType m_Type;
        VkShaderModule m_ShaderModuleHandle;
        VkPipelineShaderStageCreateInfo m_ShaderStageCreateInfo;
    };

}