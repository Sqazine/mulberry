#include "Pipeline.h"
#include "Device.h"
#include "Logger.h"

namespace mulberry::vk
{

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

    RasterPipeline::RasterPipeline()
    {
    }

    RasterPipeline::~RasterPipeline()
    {
    }

    RasterPipeline &RasterPipeline::SetVertexShader(Shader *shader)
    {
        mShaderGroup.SetVertexShader(shader);
        return *this;
    }

    RasterPipeline &RasterPipeline::SetTessellationControlShader(Shader *shader)
    {
        mShaderGroup.SetTessellationControlShader(shader);
        return *this;
    }

    RasterPipeline &RasterPipeline::SetTessellationEvaluationShader(Shader *shader)
    {
        mShaderGroup.SetTessellationEvaluationShader(shader);
        return *this;
    }

    RasterPipeline &RasterPipeline::SetGeometryShader(Shader *shader)
    {
        mShaderGroup.SetGeometryShader(shader);
        return *this;
    }

    RasterPipeline &RasterPipeline::SetFragmentShader(Shader *shader)
    {
        mShaderGroup.SetFragmentShader(shader);
        return *this;
    }

    RasterPipeline &RasterPipeline::AddVertexInputBinding(uint32_t binding, uint32_t stride)
    {
        VkVertexInputBindingDescription vertexInputBindingDesc = {};
        vertexInputBindingDesc.binding = binding;
        vertexInputBindingDesc.stride = stride;
        vertexInputBindingDesc.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        mInputBindingCache.emplace_back(vertexInputBindingDesc);

        return *this;
    }

    RasterPipeline &RasterPipeline::AddVertexInputAttribute(uint32_t binding, uint32_t location, uint32_t offset, Format format)
    {
        VkVertexInputAttributeDescription vertexInputAttribDecs = {};
        vertexInputAttribDecs.binding = binding;
        vertexInputAttribDecs.location = location;
        vertexInputAttribDecs.offset = offset;
        vertexInputAttribDecs.format = format.ToVkHandle();

        mInputAttributeCache.emplace_back(vertexInputAttribDecs);
        return *this;
    }

    RasterPipeline &RasterPipeline::SetPrimitiveTopology(PrimitiveTopology topology)
    {
        mPrimitiveTopology = topology;
        return *this;
    }
    RasterPipeline &RasterPipeline::SetPrimitiveRestartEnable(bool isOpen)
    {
        mIsPrimitiveRestartEnable = isOpen;
        return *this;
    }

    RasterPipeline &RasterPipeline::AddViewport(const Vec2 &startPos, const Vec2 &extent)
    {
        VkViewport viewPort = {};
        viewPort.x = startPos.x;
        viewPort.y = startPos.y;
        viewPort.width = extent.x;
        viewPort.height = extent.y;
        viewPort.minDepth = 0;
        viewPort.maxDepth = 1;

        mViewportCache.emplace_back(viewPort);

        return *this;
    }
    RasterPipeline &RasterPipeline::AddScissor(const Vec2 &offset, const Vec2 &extent)
    {
        VkRect2D scissor = {};
        scissor.extent.width = extent.x;
        scissor.extent.height = extent.y;
        scissor.offset.x = offset.x;
        scissor.offset.y = offset.y;
        mScissorCache.emplace_back(scissor);

        return *this;
    }

    RasterPipeline &RasterPipeline::SetCullMode(CullMode cullMode)
    {
        mCullMode = cullMode;
        return *this;
    }
    RasterPipeline &RasterPipeline::SetPolygonMode(PolygonMode mode)
    {
        mPolygonMode = mode;
        return *this;
    }
    RasterPipeline &RasterPipeline::SetFrontFace(FrontFace frontFace)
    {
        mFrontFace = frontFace;
        return *this;
    }

    RasterPipeline &RasterPipeline::SetLineWidth(float lw)
    {
        mLineWidth = lw;
        return *this;
    }

    RasterPipeline &RasterPipeline::SetRasterDiscardEnable(bool v)
    {
        mRasterDiscardEnable = v;
        return *this;
    }

    RasterPipeline &RasterPipeline::SetDepthBiasEnable(bool enable)
    {
        mDepthBiasEnable = enable;
        return *this;
    }
    RasterPipeline &RasterPipeline::SetDepthClampEnable(bool enable)
    {
        mDepthClampEnable = enable;
        return *this;
    }

    RasterPipeline &RasterPipeline::SetDepthBiasClamp(float v)
    {
        mDepthBiasClamp = v;
        return *this;
    }

    RasterPipeline &RasterPipeline::SetDepthBiasConstantFactor(float v)
    {
        mDepthBiasConstantFactor = v;
        return *this;
    }

    RasterPipeline &RasterPipeline::SetDepthBiasSlopeFactor(float v)
    {
        mDepthBiasSlopeFactor = v;
        return *this;
    }

    const VkViewport &RasterPipeline::GetViewport(uint32_t i)
    {
        return mViewportCache.at(i);
    }

    RasterPipeline &RasterPipeline::SetPipelineLayout(PipelineLayout *layout)
    {
        mLayout = layout;
        return *this;
    }

    void RasterPipeline::Build()
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

        VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateInfo{};
        inputAssemblyStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        inputAssemblyStateInfo.pNext = nullptr;
        inputAssemblyStateInfo.flags = 0;
        inputAssemblyStateInfo.topology = PRIMITIVE_TOPOLOGY_CAST(mPrimitiveTopology);
        inputAssemblyStateInfo.primitiveRestartEnable = mIsPrimitiveRestartEnable;

        VkPipelineViewportStateCreateInfo viewportStateInfo = {};
        viewportStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewportStateInfo.pNext = nullptr;
        viewportStateInfo.flags = 0;
        viewportStateInfo.scissorCount = mScissorCache.size();
        viewportStateInfo.pScissors = mScissorCache.data();
        viewportStateInfo.viewportCount = mViewportCache.size();
        viewportStateInfo.pViewports = mViewportCache.data();

        VkPipelineRasterizationStateCreateInfo rasterizationStateInfo = {};
        rasterizationStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        rasterizationStateInfo.pNext = nullptr;
        rasterizationStateInfo.flags = 0;
        rasterizationStateInfo.polygonMode = POLYGON_MODE_CAST(mPolygonMode);
        rasterizationStateInfo.frontFace = FRONT_FACE_CAST(mFrontFace);
        rasterizationStateInfo.lineWidth = mLineWidth;
        rasterizationStateInfo.rasterizerDiscardEnable = mRasterDiscardEnable;
        rasterizationStateInfo.depthBiasEnable = mDepthBiasEnable;
        rasterizationStateInfo.depthClampEnable = mDepthClampEnable;
        rasterizationStateInfo.depthBiasClamp = mDepthBiasClamp;
        rasterizationStateInfo.depthBiasConstantFactor = mDepthBiasConstantFactor;
        rasterizationStateInfo.depthBiasSlopeFactor = mDepthBiasSlopeFactor;
        rasterizationStateInfo.cullMode = CULL_MODE_CAST(mCullMode);

        VkPipelineMultisampleStateCreateInfo multiSampleStateInfo = {};
        multiSampleStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        multiSampleStateInfo.pNext = nullptr;
        multiSampleStateInfo.flags = 0;
        multiSampleStateInfo.rasterizationSamples = SAMPLE_COUNT(mSampleCount);
        multiSampleStateInfo.alphaToCoverageEnable = mIsAlphaToCoverageEnable ? VK_TRUE : VK_FALSE;
        multiSampleStateInfo.alphaToOneEnable = mIsAlphaToOneEnableEnable ? VK_TRUE : VK_FALSE;
        multiSampleStateInfo.sampleShadingEnable = mMinSampleShading == 0 ? VK_FALSE : VK_TRUE;
        multiSampleStateInfo.minSampleShading = mMinSampleShading;
        multiSampleStateInfo.pSampleMask = nullptr;

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
        info.layout = mLayout->GetHandle();
        info.pVertexInputState = &vertexInputState;
        info.pInputAssemblyState = &inputAssemblyStateInfo;
        info.pTessellationState = nullptr;
        info.pViewportState = &viewportStateInfo;
        info.pRasterizationState = &rasterizationStateInfo;
        info.pMultisampleState = &multiSampleStateInfo;
        info.pDepthStencilState = &pDepthStencilState;
        info.pColorBlendState = &pColorBlendState;
        info.pDynamicState = &dynamicState;
        info.subpass = 0;
        info.renderPass = renderPass;
        info.basePipelineIndex = -1;
        info.basePipelineHandle = VK_NULL_HANDLE;

        VK_CHECK(vkCreateGraphicsPipelines(mDevice.GetHandle(), VK_NULL_HANDLE, 1, &info, nullptr, &mHandle));
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