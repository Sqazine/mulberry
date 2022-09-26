#include "Renderer.h"
namespace  mulberry::GL
{
    std::array<int32_t, 4> Renderer::GetCurViewportInfo()
    {
        std::array<int32_t, 4> result;
        glGetIntegerv(GL_VIEWPORT, result.data());
        return result;
    }

    void Renderer::SetViewport(const std::array<int32_t, 4> &info)
    {
        glViewport(info[0], info[1], info[2], info[3]);
    }

    void Renderer::SetViewport(int32_t x, int32_t y, int32_t width, int32_t height)
    {
        glViewport(x, y, width, height);
    }

    void Renderer::ClearColorBuffer(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer::EnableDepthTest(bool active)
    {
        if (active)
            glEnable(GL_DEPTH_TEST);
        else
            glDisable(GL_DEPTH_TEST);
    }

    void Renderer::EnableCullFace(bool active)
    {
        if (active)
            glEnable(GL_CULL_FACE);
        else
            glDisable(GL_CULL_FACE);
    }

    void Renderer::Render(const IndexBuffer* ibo, RenderType mode)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo->GetID());
        glDrawElements(mode, ibo->Size(), ibo->GetDataType(), nullptr);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void Renderer::Render(uint32_t vertexCount, RenderType mode)
    {
        glDrawArrays(mode, 0, vertexCount);
    }

    void Renderer::RenderInstanced(const IndexBuffer* ibo, RenderType mode, uint32_t instanceCount)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo->GetID());
        glDrawElementsInstanced(mode, ibo->Size(), ibo->GetDataType(), nullptr, instanceCount);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void Renderer::RenderInstanced(uint32_t vertexCount, RenderType mode, uint32_t instanceCount)
    {
        glDrawArraysInstanced(mode, 0, vertexCount, instanceCount);
    }
}