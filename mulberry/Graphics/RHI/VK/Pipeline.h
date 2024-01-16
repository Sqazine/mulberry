#pragma once
#include <vulkan/vulkan.h>
#include "Object.h"
#include "Shader.h"
#include "Math/Vec2.h"
#include "Format.h"
#include "Enum.h"
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
    class Pipeline : public Object
    {
    public:
        Pipeline();
        virtual ~Pipeline();

        const VkPipeline &GetHandle();
        PipelineLayout *GetLayout() const;

    protected:
        virtual void Build() = 0;

        PipelineLayout *mLayout;
        VkPipeline mHandle;
    };

    class RasterPipeline : public Pipeline
    {
    public:
        RasterPipeline();
        ~RasterPipeline() override;

        RasterPipeline &SetVertexShader(Shader *shader);
        RasterPipeline &SetTessellationControlShader(Shader *shader);
        RasterPipeline &SetTessellationEvaluationShader(Shader *shader);
        RasterPipeline &SetGeometryShader(Shader *shader);
        RasterPipeline &SetFragmentShader(Shader *shader);

        RasterPipeline &AddVertexInputBinding(uint32_t binding, uint32_t stride);
        RasterPipeline &AddVertexInputAttribute(uint32_t binding, uint32_t location, uint32_t offset, Format format);

        RasterPipeline &SetPrimitiveTopology(PrimitiveTopology topology);
        RasterPipeline &SetPrimitiveRestartEnable(bool isOpen);

        RasterPipeline &AddViewport(const Vec2 &startPos, const Vec2 &extent);
        RasterPipeline &AddScissor(const Vec2 &offset, const Vec2 &extent);

        RasterPipeline &SetCullMode(CullMode cullMode);
        RasterPipeline &SetPolygonMode(PolygonMode mode);
        RasterPipeline &SetFrontFace(FrontFace frontFace);
        RasterPipeline &SetLineWidth(float lw);

        RasterPipeline &SetRasterDiscardEnable(bool v);

        RasterPipeline &SetDepthBiasEnable(bool enable);
        RasterPipeline &SetDepthClampEnable(bool enable);

        RasterPipeline &SetDepthBiasClamp(float v);
        RasterPipeline &SetDepthBiasConstantFactor(float v);
        RasterPipeline &SetDepthBiasSlopeFactor(float v);

        RasterPipeline &SetSampleCount(SampleCount msaa);
        RasterPipeline &SetAlphaToCoverageEnable(bool enable);
        RasterPipeline &SetAlphaToOneEnableEnable(bool enable);
        RasterPipeline &SetMinSampleShading(float v);

        RasterPipeline &SetPipelineLayout(PipelineLayout *layout);

        const VkViewport &GetViewport(uint32_t i);

        VkPipelineDepthStencilStateCreateInfo pDepthStencilState{VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO};
        VkPipelineColorBlendStateCreateInfo pColorBlendState{VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO};

        VkRenderPass renderPass;

    private:
        void Build() override;

        std::vector<VkVertexInputBindingDescription> mInputBindingCache{};
        std::vector<VkVertexInputAttributeDescription> mInputAttributeCache{};

        PrimitiveTopology mPrimitiveTopology{PrimitiveTopology::POINT_LIST};
        bool mIsPrimitiveRestartEnable{false};

        std::vector<VkViewport> mViewportCache{};
        std::vector<VkRect2D> mScissorCache{};

        CullMode mCullMode{CullMode::NONE};
        PolygonMode mPolygonMode{PolygonMode::FILL};
        FrontFace mFrontFace{FrontFace::CCW};
        float mLineWidth{1.0};
        bool mRasterDiscardEnable{false};
        bool mDepthBiasEnable{false};
        bool mDepthClampEnable{false};
        float mDepthBiasClamp{0.0};
        float mDepthBiasConstantFactor{0.0};
        float mDepthBiasSlopeFactor{0.0};

        SampleCount mSampleCount{SampleCount::X1};
        bool mIsAlphaToCoverageEnable{false};
        bool mIsAlphaToOneEnableEnable{false};
        float mMinSampleShading{0};

        RasterShaderGroup mShaderGroup;
    };

    class ComputePipeline : public Pipeline
    {
    public:
        ComputePipeline();
        ~ComputePipeline() override;

        ComputePipeline &SetShader(Shader *shader);
        ComputePipeline &SetPipelineLayout(PipelineLayout *layout);

    private:
        void Build() override;

        ComputeShaderGroup mShaderGroup;
    };
}