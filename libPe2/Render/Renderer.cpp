#include "Renderer.h"
namespace Pe2
{
    const std::string SpriteVertShader = "#version 430 core"
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

    const std::string SpriteFragShader = "#version 430 core"
                                         "in vec2 fragTexcoord;"
                                         "uniform sampler2D sprite;"
                                         "out vec4 outColor;"
                                         "void main()"
                                         "{"
                                         "	outColor=texture(sprite,fragTexcoord);"
                                         "}";

    Primitive SpriteRenderer::m_SpritePrimitive;

    void SpriteRenderer::Render()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_SpritePrimitive.GetIndexBuffer()->GetID());
        glDrawElements(GL_TRIANGLES, m_SpritePrimitive.GetIndexBuffer()->Size(), m_SpritePrimitive.GetIndexBuffer()->GetDataType(), nullptr);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void SpriteRenderer::RenderInstanced(uint32_t instanceCount)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_SpritePrimitive.GetIndexBuffer()->GetID());
        glDrawElementsInstanced(GL_TRIANGLES, m_SpritePrimitive.GetIndexBuffer()->Size(), m_SpritePrimitive.GetIndexBuffer()->GetDataType(), nullptr, instanceCount);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}