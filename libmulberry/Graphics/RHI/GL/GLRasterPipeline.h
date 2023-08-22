#pragma once
#include <cstdint>
#include <memory>
#include <glad/glad.h>
#include <array>
#include "GLIndexBuffer.h"
#include "Graphics/RHI/RasterPipeline.h"

namespace mulberry
{

	class GLRasterPipeline
	{
	public:
		GLRasterPipeline();
		GLRasterPipeline(const RasterPipelineConfig &config);
		~GLRasterPipeline();

		void SetBufferClearColor(const Color &color);
		void ClearColorBuffer();

		Viewport GetViewport() const;
		void SetViewport(const Viewport &info);

		void SetPointSize(uint32_t size);
		uint32_t GetPointSize() const;

		void SetCull(CullType cullType);
		const CullType &GetCullType() const;

		void SetDepthTest(DepthTestType depthTest);
		const DepthTestType &GetDepthTest() const;

		void SetDepthMask(DepthMask depthMask);
		const DepthMask &GetDepthMask() const;

		void SetStencilMask(StencilMask stencilMask);
        const StencilMask &GetStencilMask() const;

		void SetBlendState(bool isOpen, BlendFunc srcFunc, BlendFunc dstFunc);
		std::tuple<bool, BlendFunc, BlendFunc> GetBlendState() const;

		void Render(const GLIndexBuffer *ibo, PrimitiveRenderType mode);
		void RenderInstanced(const GLIndexBuffer *ibo, PrimitiveRenderType mode, uint32_t instanceCount);

	private:
		RasterPipelineConfig mConfig;
	};

}