#include "SpriteRenderer.h"
namespace Pe2
{
    const std::string SpriteVertShader = "#version 330 core"
                                         "uniform mat4 modelMat;"
                                         "uniform mat4 viewMat;"
                                         "uniform mat4 projMat;"
                                         "layout(location=0) in vec2 inPosition;"
                                         "layout(location=1) in vec2 inTexcoord;"
                                         "out vec2 fragTexcoord;"
                                         "void main()"
                                         "{"
                                         "	gl_Position=projMat*viewMat*modelMat*vec4(inPosition,0.0,1.0);"
                                         "	fragTexcoord=inTexcoord;"
                                         "}";

    const std::string SpriteFragShader = "#version 330 core"
                                         "in vec2 fragTexcoord;"
                                         "uniform sampler2D sprite;"
                                         "out vec4 outColor;"
                                         "void main()"
                                         "{"
                                         "	outColor=texture(sprite,fragTexcoord);"
                                         "}";

    Quad SpriteRenderer::m_SpriteQuad;

    void SpriteRenderer::ClearColorBuffer(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void SpriteRenderer::Render(SpriteRenderType mode)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_SpriteQuad.GetIndexBuffer()->GetID());
        glDrawElements(mode, m_SpriteQuad.GetIndexBuffer()->Size(), m_SpriteQuad.GetIndexBuffer()->GetDataType(), nullptr);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void SpriteRenderer::RenderInstanced(SpriteRenderType mode, uint32_t instanceCount)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_SpriteQuad.GetIndexBuffer()->GetID());
        glDrawElementsInstanced(mode, m_SpriteQuad.GetIndexBuffer()->Size(), m_SpriteQuad.GetIndexBuffer()->GetDataType(), nullptr, instanceCount);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}