#include "Pipeline.h"
#include "Device.h"
#include "Logger.h"

namespace mulberry::rhi::vk
{
    PipelineLayout::PipelineLayout()
        : mHandle(VK_NULL_HANDLE)
    {
    }

    PipelineLayout::~PipelineLayout()
    {
        if (mHandle)
            vkDestroyPipelineLayout(mDevice.GetHandle(), mHandle, nullptr);
    }

    PipelineLayout &PipelineLayout::AddDescriptorSetLayout(DescriptorSetLayout *descriptorSetLayout)
    {
        mDescriptorSetLayoutCache.emplace_back(descriptorSetLayout);

        return *this;
    }

    PipelineLayout &PipelineLayout::SetDescriptorSetLayouts(const std::vector<DescriptorSetLayout *> &descriptorSetLayouts)
    {
        mDescriptorSetLayoutCache = descriptorSetLayouts;

        return *this;
    }

    const VkPipelineLayout &PipelineLayout::GetHandle()
    {
        if (mHandle == VK_NULL_HANDLE)
            Build();
        return mHandle;
    }

    void PipelineLayout::Build()
    {

        std::vector<VkDescriptorSetLayout> rawLayout(mDescriptorSetLayoutCache.size());

        for (int32_t i = 0; i < rawLayout.size(); ++i)
            rawLayout[i] = mDescriptorSetLayoutCache[i]->GetHandle();

        VkPipelineLayoutCreateInfo info = {};
        info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        info.pNext = nullptr;
        info.flags = 0;
        info.setLayoutCount = rawLayout.size();
        info.pSetLayouts = rawLayout.data();
        info.pushConstantRangeCount = 0;
        info.pPushConstantRanges = nullptr;

        VK_CHECK(vkCreatePipelineLayout(mDevice.GetHandle(), &info, nullptr, &mHandle));

        mDescriptorSetLayoutCache.clear();
    }

    Pipeline::Pipeline()
        : mLayout(nullptr), mHandle(VK_NULL_HANDLE)
    {
    }
    Pipeline::~Pipeline()
    {
        if (mHandle)
            vkDestroyPipeline(mDevice.GetHandle(), mHandle, nullptr);
    }

    const VkPipeline &Pipeline::GetHandle()
    {
        if (mHandle == VK_NULL_HANDLE)
            Build();
        return mHandle;
    }

    PipelineLayout *Pipeline::GetLayout() const
    {
        return mLayout;
    }

    GraphicsPipeline::GraphicsPipeline()
    {
    }

    GraphicsPipeline::~GraphicsPipeline()
    {
    }

    GraphicsPipeline &GraphicsPipeline::SetVertexShader(Shader *shader)
    {
        mShaderGroup.SetVertexShader(shader);
        return *this;
    }

    GraphicsPipeline &GraphicsPipeline::SetTessellationControlShader(Shader *shader)
    {
        mShaderGroup.SetTessellationControlShader(shader);
        return *this;
    }

    GraphicsPipeline &GraphicsPipeline::SetTessellationEvaluationShader(Shader *shader)
    {
        mShaderGroup.SetTessellationEvaluationShader(shader);
        return *this;
    }

    GraphicsPipeline &GraphicsPipeline::SetGeometryShader(Shader *shader)
    {
        mShaderGroup.SetGeometryShader(shader);
        return *this;
    }

    GraphicsPipeline &GraphicsPipeline::SetFragmentShader(Shader *shader)
    {
        mShaderGroup.SetFragmentShader(shader);
        return *this;
    }

    GraphicsPipeline &GraphicsPipeline::AddVertexInputBinding(uint32_t binding, uint32_t stride)
    {
        VkVertexInputBindingDescription vertexInputBindingDesc = {};
        vertexInputBindingDesc.binding = binding;
        vertexInputBindingDesc.stride = stride;
        vertexInputBindingDesc.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        mInputBindingCache.emplace_back(vertexInputBindingDesc);

        return *this;
    }

    GraphicsPipeline &GraphicsPipeline::AddVertexInputAttribute(uint32_t binding, uint32_t location, uint32_t offset, Format format)
    {
        VkVertexInputAttributeDescription vertexInputAttribDecs = {};
        vertexInputAttribDecs.binding = binding;
        vertexInputAttribDecs.location = location;
        vertexInputAttribDecs.offset = offset;
        vertexInputAttribDecs.format = format.ToVkHandle();

        mInputAttributeCache.emplace_back(vertexInputAttribDecs);
        return *this;
    }

    GraphicsPipeline &GraphicsPipeline::SetPrimitiveTopology(PrimitiveTopology topology)
    {
        SET(mInputAssemblyStateInfo.topology, ToVkPrimitiveTopology(topology));
    }
    GraphicsPipeline &GraphicsPipeline::SetPrimitiveRestartEnable(bool isOpen)
    {
        mInputAssemblyStateInfo.primitiveRestartEnable = isOpen;
        mIsDirty = true;
        return *this;
    }

    GraphicsPipeline &GraphicsPipeline::SetCullMode(CullMode cullMode)
    {
        mCullMode = cullMode;
        return *this;
    }
    GraphicsPipeline &GraphicsPipeline::SetPolygonMode(PolygonMode mode)
    {
        mPolygonMode = mode;
        return *this;
    }
    GraphicsPipeline &GraphicsPipeline::SetFrontFace(FrontFace frontFace)
    {
        mFrontFace = frontFace;
        return *this;
    }

    GraphicsPipeline &GraphicsPipeline::SetLineWidth(float lw)
    {
        mLineWidth = lw;
        return *this;
    }

    GraphicsPipeline &GraphicsPipeline::SetRasterDiscardEnable(bool v)
    {
        mRasterDiscardEnable = v;
        return *this;
    }

    GraphicsPipeline &GraphicsPipeline::SetDepthBiasEnable(bool enable)
    {
        mDepthBiasEnable = enable;
        return *this;
    }
    GraphicsPipeline &GraphicsPipeline::SetDepthClampEnable(bool enable)
    {
        mDepthClampEnable = enable;
        return *this;
    }

    GraphicsPipeline &GraphicsPipeline::SetDepthBiasClamp(float v)
    {
        mDepthBiasClamp = v;
        return *this;
    }

    GraphicsPipeline &GraphicsPipeline::SetDepthBiasConstantFactor(float v)
    {
        mDepthBiasConstantFactor = v;
        return *this;
    }

    GraphicsPipeline &GraphicsPipeline::SetDepthBiasSlopeFactor(float v)
    {
        mDepthBiasSlopeFactor = v;
        return *this;
    }

    GraphicsPipeline &GraphicsPipeline::SetSampleCount(SampleCount msaa)
    {
        mMultiSampleStateInfo.rasterizationSamples = ToVkSampleCount(msaa);
        mIsDirty = true;
        return *this;
    }
    GraphicsPipeline &GraphicsPipeline::SetAlphaToCoverageEnable(bool enable)
    {
        mMultiSampleStateInfo.alphaToCoverageEnable = enable;
        mIsDirty = true;
        return *this;
    }
    GraphicsPipeline &GraphicsPipeline::SetAlphaToOneEnable(bool enable)
    {
        mMultiSampleStateInfo.alphaToCoverageEnable = enable;
        mIsDirty = true;
        return *this;
    }
    GraphicsPipeline &GraphicsPipeline::SetMinSampleShading(float v)
    {
        mMultiSampleStateInfo.sampleShadingEnable = (v == 0 ? VK_FALSE : VK_TRUE);
        mMultiSampleStateInfo.minSampleShading = v;
        mIsDirty = true;
        return *this;
    }

    GraphicsPipeline &GraphicsPipeline::SetPipelineLayout(PipelineLayout *layout)
    {
        mLayout = layout;
        return *this;
    }

    GraphicsPipeline &GraphicsPipeline::SetRenderPass(RenderPass *renderPass)
    {
        mRenderPass = renderPass;
        return *this;
    }

    void GraphicsPipeline::Build()
    {
        if (mIsDirty)
        {
            auto shaderStages = mShaderGroup.GetShaderStages();

            VkPipelineVertexInputStateCreateInfo vertexInputState{};
            vertexInputState.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
            vertexInputState.pNext = nullptr;
            vertexInputState.flags = 0;
            vertexInputState.vertexAttributeDescriptionCount = mInputAttributeCache.size();
            vertexInputState.pVertexAttributeDescriptions = mInputAttributeCache.data();
            vertexInputState.vertexBindingDescriptionCount = mInputBindingCache.size();
            vertexInputState.pVertexBindingDescriptions = mInputBindingCache.data();

            VkRect2D scissor{};
            scissor.extent = {0, 0};
            scissor.offset = {0, 0};

            VkViewport viewport{};
            viewport.x = 0;
            viewport.y = 0;
            viewport.width = 0;
            viewport.height = 0;
            viewport.minDepth = 0.0f;
            viewport.maxDepth = 1.0f;

            VkPipelineViewportStateCreateInfo viewportStateInfo = {};
            viewportStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
            viewportStateInfo.pNext = nullptr;
            viewportStateInfo.flags = 0;
            viewportStateInfo.scissorCount = 1;
            viewportStateInfo.pScissors = &scissor;
            viewportStateInfo.viewportCount = 1;
            viewportStateInfo.pViewports = &viewport;

            std::vector<VkDynamicState> dynamicStates = {
                VK_DYNAMIC_STATE_VIEWPORT,
                VK_DYNAMIC_STATE_SCISSOR,
                VK_DYNAMIC_STATE_LINE_WIDTH,
                VK_DYNAMIC_STATE_DEPTH_BIAS,
                VK_DYNAMIC_STATE_BLEND_CONSTANTS,
                VK_DYNAMIC_STATE_DEPTH_BOUNDS,
                VK_DYNAMIC_STATE_STENCIL_COMPARE_MASK,
                VK_DYNAMIC_STATE_STENCIL_WRITE_MASK,
                VK_DYNAMIC_STATE_STENCIL_REFERENCE,
            };

            VkPipelineDynamicStateCreateInfo dynamicState{};
            dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
            dynamicState.flags = 0;
            dynamicState.pNext = nullptr;
            dynamicState.dynamicStateCount = dynamicStates.size();
            dynamicState.pDynamicStates = dynamicStates.data();

            VkGraphicsPipelineCreateInfo info{};
            info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
            info.pNext = nullptr;
            info.flags = 0;
            info.stageCount = shaderStages.size();
            info.pStages = shaderStages.data();
            info.layout = mLayout ? mLayout->GetHandle() : nullptr;
            info.pVertexInputState = &vertexInputState;
            info.pInputAssemblyState = &mInputAssemblyStateInfo;
            info.pTessellationState = nullptr;
            info.pViewportState = &viewportStateInfo;
            info.pRasterizationState = &mRasterizationStateInfo;
            info.pMultisampleState = &mMultiSampleStateInfo;
            info.pDepthStencilState = &pDepthStencilState;
            info.pColorBlendState = &pColorBlendState;
            info.pDynamicState = &dynamicState;
            info.subpass = 0;
            info.renderPass = mRenderPass->GetHandle();
            info.basePipelineIndex = -1;
            info.basePipelineHandle = VK_NULL_HANDLE;

            VK_CHECK(vkCreateGraphicsPipelines(mDevice.GetHandle(), VK_NULL_HANDLE, 1, &info, nullptr, &mHandle));
        }
    }

    ComputePipeline::ComputePipeline()
    {
    }

    ComputePipeline::~ComputePipeline()
    {
    }

    ComputePipeline &ComputePipeline::SetShader(Shader *shader)
    {
        mShaderGroup.SetShader(shader);
        return *this;
    }

    ComputePipeline &ComputePipeline::SetPipelineLayout(PipelineLayout *layout)
    {
        mLayout = layout;
        return *this;
    }

    void ComputePipeline::Build()
    {
        VkComputePipelineCreateInfo pipelineInfo{};
        pipelineInfo.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
        pipelineInfo.pNext = nullptr;
        pipelineInfo.flags = 0;
        pipelineInfo.stage = mShaderGroup.GetShaderStage();
        pipelineInfo.layout = mLayout->GetHandle();
        pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
        pipelineInfo.basePipelineIndex = -1;

        VK_CHECK(vkCreateComputePipelines(mDevice.GetHandle(), nullptr, 1, &pipelineInfo, nullptr, &mHandle));
    }
}