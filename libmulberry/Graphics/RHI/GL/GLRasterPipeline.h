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
		GLRasterPipeline(const RasterPipelineState &state);
		~GLRasterPipeline();

		void SetPSO(const RasterPipelineState &state);
		const RasterPipelineState &GetPSO() const;
		RasterPipelineState &GetPSO();

		void Render(const GLIndexBuffer *ibo);
		void RenderInstanced(const GLIndexBuffer *ibo, uint32_t instanceCount);

	private:
		RasterPipelineState mState;
	};

}