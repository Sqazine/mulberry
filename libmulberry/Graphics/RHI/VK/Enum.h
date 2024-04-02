#pragma once
#include <cstdint>
#include <vulkan/vulkan.h>
#include <type_traits>
#include "Utils/Utils.h"
#include "RHI/Enum.h"

namespace mulberry::vk
{
    enum class BufferUsage : uint64_t
    {
#define ITEM(x) x = VK_BUFFER_USAGE_##x##_BIT
#define ITEM_KHR(x) x = VK_BUFFER_USAGE_##x##_BIT_KHR
#define ITEM_EXT(x) x = VK_BUFFER_USAGE_##x##_BIT_EXT
#define ITEM_BUFFER(x) x = VK_BUFFER_USAGE_##x##_BUFFER_BIT
#define ITEM_BUFFER_EXT(x) x = VK_BUFFER_USAGE_##x##_BUFFER_BIT_EXT
        ITEM(TRANSFER_SRC),
        ITEM(TRANSFER_DST),
        ITEM_BUFFER(UNIFORM_TEXEL),
        ITEM_BUFFER(STORAGE_TEXEL),
        ITEM_BUFFER(UNIFORM),
        ITEM_BUFFER(STORAGE),
        ITEM_BUFFER(INDEX),
        ITEM_BUFFER(VERTEX),
        ITEM_BUFFER(INDIRECT),
        ITEM(SHADER_DEVICE_ADDRESS),
        ITEM_BUFFER_EXT(TRANSFORM_FEEDBACK),
        ITEM_BUFFER_EXT(TRANSFORM_FEEDBACK_COUNTER),
        ITEM_EXT(CONDITIONAL_RENDERING),
        ITEM_KHR(ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY),
        ITEM_KHR(ACCELERATION_STRUCTURE_STORAGE),
        ITEM_KHR(SHADER_BINDING_TABLE),
        ITEM_BUFFER_EXT(SAMPLER_DESCRIPTOR),
        ITEM_BUFFER_EXT(RESOURCE_DESCRIPTOR),
        ITEM_BUFFER_EXT(PUSH_DESCRIPTORS_DESCRIPTOR),
        ITEM_EXT(MICROMAP_BUILD_INPUT_READ_ONLY),
        ITEM_EXT(MICROMAP_STORAGE),
#undef ITEM
#undef ITEM_KHR
#undef ITEM_EXT
#undef ITEM_BUFFER
#undef ITEM_BUFFER_EXT
    };

#define BUFFER_USAGE_CAST(t) (static_cast<VkBufferUsageFlags>(std::underlying_type<BufferUsage>::type(t)))
    ENUM_CLASS_OP(BUFFER_USAGE_CAST, BufferUsage, VkBufferUsageFlags);

    enum class MemoryProperty : uint64_t
    {
#define ITEM(x) x = VK_MEMORY_PROPERTY_##x##_BIT
        ITEM(DEVICE_LOCAL),
        ITEM(HOST_VISIBLE),
        ITEM(HOST_COHERENT),
        ITEM(HOST_CACHED),
        ITEM(LAZILY_ALLOCATED),
        ITEM(PROTECTED),
#undef ITEM
    };

#define MEMORY_PROPERTY_CAST(t) (static_cast<VkMemoryPropertyFlags>(std::underlying_type<MemoryProperty>::type(t)))
    ENUM_CLASS_OP(MEMORY_PROPERTY_CAST, MemoryProperty, VkMemoryPropertyFlags);

    enum class DescriptorType : uint64_t
    {
#define ITEM(x) x = VK_DESCRIPTOR_TYPE_##x
        ITEM(SAMPLER),
        ITEM(COMBINED_IMAGE_SAMPLER),
        ITEM(SAMPLED_IMAGE),
        ITEM(STORAGE_IMAGE),
        ITEM(UNIFORM_TEXEL_BUFFER),
        ITEM(STORAGE_TEXEL_BUFFER),
        ITEM(UNIFORM_BUFFER),
        ITEM(STORAGE_BUFFER),
        ITEM(UNIFORM_BUFFER_DYNAMIC),
        ITEM(STORAGE_BUFFER_DYNAMIC),
        ITEM(INPUT_ATTACHMENT),
        ITEM(INLINE_UNIFORM_BLOCK),
        ITEM(ACCELERATION_STRUCTURE_KHR),
        ITEM(ACCELERATION_STRUCTURE_NV),
        ITEM(SAMPLE_WEIGHT_IMAGE_QCOM),
        ITEM(BLOCK_MATCH_IMAGE_QCOM),
        ITEM(MUTABLE_EXT),
#undef ITEM
    };
#define DESCRIPTOR_TYPE_CAST(t) (static_cast<VkDescriptorType>(std::underlying_type<DescriptorType>::type(t)))
    ENUM_CLASS_OP(DESCRIPTOR_TYPE_CAST, DescriptorType, VkDescriptorType);

    enum class ImageUsage : uint64_t
    {
#define ITEM(x) x = VK_IMAGE_USAGE_##x##_BIT
#define ITEM_KHR(x) x = VK_IMAGE_USAGE_##x##_BIT_KHR
        ITEM(TRANSFER_SRC),
        ITEM(TRANSFER_DST),
        ITEM(SAMPLED),
        ITEM(STORAGE),
        ITEM(COLOR_ATTACHMENT),
        ITEM(DEPTH_STENCIL_ATTACHMENT),
        ITEM(TRANSIENT_ATTACHMENT),
        ITEM(INPUT_ATTACHMENT),
        ITEM_KHR(FRAGMENT_SHADING_RATE_ATTACHMENT),
#undef ITEM
#undef ITEM_KHR
    };
#define IMAGE_USAGE_CAST(t) (static_cast<VkImageUsageFlags>(std::underlying_type<ImageUsage>::type(t)))
    ENUM_CLASS_OP(IMAGE_USAGE_CAST, ImageUsage, VkImageUsageFlags)

    enum class ImageLayout : uint64_t
    {
#define ITEM(x) x = VK_IMAGE_LAYOUT_##x
        ITEM(UNDEFINED),
        ITEM(GENERAL),
        ITEM(COLOR_ATTACHMENT_OPTIMAL),
        ITEM(DEPTH_STENCIL_ATTACHMENT_OPTIMAL),
        ITEM(DEPTH_STENCIL_READ_ONLY_OPTIMAL),
        ITEM(SHADER_READ_ONLY_OPTIMAL),
        ITEM(TRANSFER_SRC_OPTIMAL),
        ITEM(TRANSFER_DST_OPTIMAL),
        ITEM(PREINITIALIZED),
        ITEM(DEPTH_READ_ONLY_STENCIL_ATTACHMENT_OPTIMAL),
        ITEM(DEPTH_ATTACHMENT_STENCIL_READ_ONLY_OPTIMAL),
        ITEM(DEPTH_ATTACHMENT_OPTIMAL),
        ITEM(DEPTH_READ_ONLY_OPTIMAL),
        ITEM(STENCIL_ATTACHMENT_OPTIMAL),
        ITEM(STENCIL_READ_ONLY_OPTIMAL),
        ITEM(READ_ONLY_OPTIMAL),
        ITEM(ATTACHMENT_OPTIMAL),
        ITEM(PRESENT_SRC_KHR),
#undef ITEM
    };

#define IMAGE_LAYOUT_CAST(t) (static_cast<VkImageLayout>(std::underlying_type<ImageLayout>::type(t)))
    ENUM_CLASS_OP(IMAGE_LAYOUT_CAST, ImageLayout, VkImageLayout);

    enum class ImageAspect : uint64_t
    {
#define ITEM(x) x = VK_IMAGE_ASPECT_##x
#define ITEM_BIT(x) x = VK_IMAGE_ASPECT_##x##_BIT
        ITEM(NONE),
        ITEM_BIT(COLOR),
        ITEM_BIT(DEPTH),
        ITEM_BIT(STENCIL),
#undef ITEM
#undef ITEM_BIT
    };

#define IMAGE_ASPECT_CAST(imageAspect) (static_cast<VkImageAspectFlags>(std::underlying_type<ImageAspect>::type(imageAspect)))
    ENUM_CLASS_OP(IMAGE_ASPECT_CAST, ImageAspect, VkImageAspectFlags);

    enum class ImageTiling : uint64_t
    {
#define ITEM(x) x = VK_IMAGE_TILING_##x
        ITEM(OPTIMAL),
        ITEM(LINEAR),
#undef ITEM
    };
#define IMAGE_TILING_CAST(imageTiling) (static_cast<VkImageTiling>(std::underlying_type<ImageTiling>::type(imageTiling)))
    ENUM_CLASS_OP(IMAGE_TILING_CAST, ImageTiling, VkImageTiling);

    enum class PipelineStage : uint64_t
    {
#define ITEM_NO_POSTFIX(x) VK_PIPELINE_STAGE_##x
#define ITEM(x) x = VK_PIPELINE_STAGE_##x##_BIT
#define ITEM_EXT(x) x = VK_PIPELINE_STAGE_##x##_BIT_EXT
#define ITEM_KHR(x) x = VK_PIPELINE_STAGE_##x##_BIT_KHR

        ITEM_NO_POSTFIX(NONE),
        ITEM(TOP_OF_PIPE),
        ITEM(BOTTOM_OF_PIPE),
        ITEM(DRAW_INDIRECT),
        ITEM(VERTEX_INPUT),

        ITEM(VERTEX_SHADER),
        ITEM(TESSELLATION_CONTROL_SHADER),
        ITEM(TESSELLATION_EVALUATION_SHADER),
        ITEM(GEOMETRY_SHADER),
        ITEM(FRAGMENT_SHADER),
        ITEM(COMPUTE_SHADER),

        ITEM(EARLY_FRAGMENT_TESTS),

        ITEM(LATE_FRAGMENT_TESTS),
        ITEM(COLOR_ATTACHMENT_OUTPUT),

        ITEM(TRANSFER),

        ITEM(HOST),

        ITEM(ALL_GRAPHICS),
        ITEM(ALL_COMMANDS),

        ITEM_EXT(TASK_SHADER),
        ITEM_EXT(MESH_SHADER),
        ITEM_EXT(TRANSFORM_FEEDBACK),
        ITEM_EXT(CONDITIONAL_RENDERING),
        ITEM_EXT(FRAGMENT_DENSITY_PROCESS),

        ITEM_KHR(ACCELERATION_STRUCTURE_BUILD),
        ITEM_KHR(RAY_TRACING_SHADER),
        ITEM_KHR(FRAGMENT_SHADING_RATE_ATTACHMENT),

#undef ITEM_NO_POSTFIX
#undef ITEM
#undef ITEM_EXT
#undef ITEM_KHR
    };
#define PIPELINE_STAGE_CAST(pielineStage) (static_cast<VkPipelineStageFlagBits>(std::underlying_type<PipelineStage>::type(pielineStage)))
    ENUM_CLASS_OP(PIPELINE_STAGE_CAST, PipelineStage, VkPipelineStageFlagBits);

    enum class Access : uint64_t
    {
#define ITEM(x) x = VK_ACCESS_##x
#define ITEM_BIT(x) x = VK_ACCESS_##x##_BIT
#define ITEM_EXT(x) x = VK_ACCESS_##x##_BIT_EXT
#define ITEM_KHR(x) x = VK_ACCESS_##x##_BIT_KHR
        ITEM(NONE),
        ITEM_BIT(INDIRECT_COMMAND_READ),
        ITEM_BIT(INDEX_READ),
        ITEM_BIT(VERTEX_ATTRIBUTE_READ),
        ITEM_BIT(UNIFORM_READ),
        ITEM_BIT(INPUT_ATTACHMENT_READ),
        ITEM_BIT(SHADER_READ),
        ITEM_BIT(SHADER_WRITE),
        ITEM_BIT(COLOR_ATTACHMENT_READ),
        ITEM_BIT(COLOR_ATTACHMENT_WRITE),
        ITEM_BIT(DEPTH_STENCIL_ATTACHMENT_READ),
        ITEM_BIT(DEPTH_STENCIL_ATTACHMENT_WRITE),
        ITEM_BIT(TRANSFER_READ),
        ITEM_BIT(TRANSFER_WRITE),
        ITEM_BIT(HOST_READ),
        ITEM_BIT(HOST_WRITE),
        ITEM_BIT(MEMORY_READ),
        ITEM_BIT(MEMORY_WRITE),
        ITEM_EXT(TRANSFORM_FEEDBACK_WRITE),
        ITEM_EXT(TRANSFORM_FEEDBACK_COUNTER_READ),
        ITEM_EXT(TRANSFORM_FEEDBACK_COUNTER_WRITE),
        ITEM_EXT(CONDITIONAL_RENDERING_READ),
        ITEM_EXT(COLOR_ATTACHMENT_READ_NONCOHERENT),
        ITEM_KHR(ACCELERATION_STRUCTURE_READ),
        ITEM_KHR(ACCELERATION_STRUCTURE_WRITE),
#undef ITEM
#undef ITEM_BIT
#undef ITEM_EXT
#undef ITEM_KHR
    };
#define ACCESS_CAST(access) (static_cast<VkAccessFlagBits>(std::underlying_type<Access>::type(access)))
    ENUM_CLASS_OP(ACCESS_CAST, Access, VkAccessFlagBits);
}