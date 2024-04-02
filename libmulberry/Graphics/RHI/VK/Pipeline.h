#pragma once
#include <vulkan/vulkan.h>
#include "Base.h"
#include "Shader.h"
#include "Math/Vec2.h"
#include "Format.h"
#include "Enum.h"
#include "RenderPass.h"
#include "Descriptor.h"

namespace mulberry::vk
{
    class PipelineLayout : public Base
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
    class Pipeline : public Base
    {
    public:
        Pipeline();
        virtual ~Pipeline();

        const VkPipeline &GetHandle();
        PipelineLayout *GetLayout() const;

    protected:
        virtual void Build() = 0;

        bool mIsDirty;

        PipelineLayout *mLayout;
        VkPipeline mHandle;
    };

    class GraphicsPipeline : public Pipeline
    {
    public:
        GraphicsPipeline();
        ~GraphicsPipeline() override;

        GraphicsPipeline &SetVertexShader(Shader *shader);
        GraphicsPipeline &SetTessellationControlShader(Shader *shader);
        GraphicsPipeline &SetTessellationEvaluationShader(Shader *shader);
        GraphicsPipeline &SetGeometryShader(Shader *shader);
        GraphicsPipeline &SetFragmentShader(Shader *shader);

        GraphicsPipeline &AddVertexInputBinding(uint32_t binding, uint32_t stride);
        GraphicsPipeline &AddVertexInputAttribute(uint32_t binding, uint32_t location, uint32_t offset, Format format);

        GraphicsPipeline &SetPrimitiveTopology(PrimitiveTopology topology);
        GraphicsPipeline &SetPrimitiveRestartEnable(bool isOpen);

        GraphicsPipeline &SetCullMode(CullMode cullMode);
        GraphicsPipeline &SetPolygonMode(PolygonMode mode);
        GraphicsPipeline &SetFrontFace(FrontFace frontFace);
        GraphicsPipeline &SetLineWidth(float lw);

        GraphicsPipeline &SetRasterDiscardEnable(bool v);

        GraphicsPipeline &SetDepthBiasEnable(bool enable);
        GraphicsPipeline &SetDepthClampEnable(bool enable);

        GraphicsPipeline &SetDepthBiasClamp(float v);
        GraphicsPipeline &SetDepthBiasConstantFactor(float v);
        GraphicsPipeline &SetDepthBiasSlopeFactor(float v);

        GraphicsPipeline &SetSampleCount(SampleCount msaa);
        GraphicsPipeline &SetAlphaToCoverageEnable(bool enable);
        GraphicsPipeline &SetAlphaToOneEnable(bool enable);
        GraphicsPipeline &SetMinSampleShading(float v);

        GraphicsPipeline &SetPipelineLayout(PipelineLayout *layout);

        GraphicsPipeline &SetRenderPass(class RenderPass *renderPass);

        VkPipelineDepthStencilStateCreateInfo pDepthStencilState{VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO};
        VkPipelineColorBlendStateCreateInfo pColorBlendState{VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO};
    private:
        void Build() override;

        std::vector<VkVertexInputBindingDescription> mInputBindingCache{};
        std::vector<VkVertexInputAttributeDescription> mInputAttributeCache{};

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

        VkPipelineMultisampleStateCreateInfo mMultiSampleStateInfo{VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO};
        VkPipelineInputAssemblyStateCreateInfo mInputAssemblyStateInfo{VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO};
        VkPipelineRasterizationStateCreateInfo mRasterizationStateInfo{VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO};

        class RenderPass *mRenderPass{nullptr};

        GraphicsShaderGroup mShaderGroup;
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