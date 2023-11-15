#include "GLRasterPipeline.h"
#include <unordered_map>
#include "Graphics/Primitive.h"
#include "GL/GLUtils.h"
namespace mulberry
{
    GLRasterPipeline::GLRasterPipeline()
    {
    }

    GLRasterPipeline::GLRasterPipeline(const RasterPipelineState &state)
        : mState(state)
    {
    }

    GLRasterPipeline::~GLRasterPipeline()
    {
    }

    void GLRasterPipeline::SetPSO(const RasterPipelineState &state)
    {
        mState = state;
    }
    const RasterPipelineState &GLRasterPipeline::GetPSO() const
    {
        return mState;
    }
    RasterPipelineState &GLRasterPipeline::GetPSO()
    {
        return mState;
    }

    void GLRasterPipeline::Render(const GLIndexBuffer *ibo)
    {
        ToGLRawPSO(mState);

        glEnable(GL_MULTISAMPLE);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo->GetHandle());
        glDrawElements(ToGLPrimitiveRenderType(mState.primitiveRenderType), ibo->Size(), ibo->GetDataType(), nullptr);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        ToDefaultGLRawPSO();
    }

    void GLRasterPipeline::RenderInstanced(const GLIndexBuffer *ibo, uint32_t instanceCount)
    {
        ToGLRawPSO(mState);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo->GetHandle());
        glDrawElementsInstanced(ToGLPrimitiveRenderType(mState.primitiveRenderType), ibo->Size(), ibo->GetDataType(), nullptr, instanceCount);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        ToDefaultGLRawPSO();
    }
}