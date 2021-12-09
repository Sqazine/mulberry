#include "Renderer.h"
#include "../Scene/Component/SpriteComponent.h"
namespace Pe2
{
    const std::string spriteVertShader = "#version 430 core"
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

    const std::string spriteFragShader = "#version 430 core"
                                         "in vec2 fragTexcoord;"
                                         "layout(location=0) uniform sampler2D sprite;"
                                         "out vec4 outColor;"
                                         "void main()"
                                         "{"
                                         "	outColor=texture(sprite,fragTexcoord);"
                                         "}";

    const std::string gizmoVertShader = "#version 430 core"
                                        "uniform mat4 modelMat;"
                                        "uniform mat4 viewMat;"
                                        "uniform mat4 projMat;"
                                        "layout(location=0) in vec2 inPosition;"
                                        "out vec2 fragTexcoord;"
                                        "void main()"
                                        "{"
                                        "	gl_Position=projMat*viewMat*modelMat*vec4(inPosition,0.0,1.0);"
                                        "}";

    const std::string gizmoFragShader = "#version 430 core"
                                        "in vec2 fragTexcoord;"
                                        "out vec4 outColor;"
                                        "void main()"
                                        "{"
                                        "	outColor=vec4(0.0,1.0,0.0,1.0);"
                                        "}";

    Primitive SpriteRenderer::m_SpritePrimitive;

    void SpriteRenderer::Init()
    {
        auto vertShader = ShaderModule();
        vertShader.CompileSource(VERTEX_SHADER, spriteVertShader);
        auto fragShader = ShaderModule();
        fragShader.CompileSource(FRAGMENT_SHADER, spriteFragShader);
        m_SpriteShaderProgram = ShaderProgram();
        m_SpriteShaderProgram.AttachShader(&vertShader);
        m_SpriteShaderProgram.AttachShader(&fragShader);
    }

    void SpriteRenderer::Render(const Entity *entity)
    {
        m_SpriteShaderProgram.SetActive(true);
        //not check is nullptr
        SpriteComponent *spriteComp = entity->GetComponent<SpriteComponent>();

        spriteComp->GetTexture()->BindTo(m_SpriteShaderProgram.GetAttribute("sprite"), 0);

        m_SpritePrimitive.Bind(m_SpriteShaderProgram.GetAttribute("inPosition"), m_SpriteShaderProgram.GetAttribute("inTexcoord"));
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_SpritePrimitive.GetIndexBuffer()->GetID());
        glDrawElements(GL_TRIANGLES, m_SpritePrimitive.GetIndexBuffer()->Size(), m_SpritePrimitive.GetIndexBuffer()->GetDataType(), nullptr);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        m_SpritePrimitive.UnBind(m_SpriteShaderProgram.GetAttribute("inPosition"), m_SpriteShaderProgram.GetAttribute("inTexcoord"));

        spriteComp->GetTexture()->UnBindFrom(m_SpriteShaderProgram.GetAttribute("sprite"));

        m_SpriteShaderProgram.SetActive(false);
    }

    void SpriteRenderer::RenderInstanced(const std::vector<Entity *> entities)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_SpritePrimitive.GetIndexBuffer()->GetID());
        glDrawElementsInstanced(GL_TRIANGLES, m_SpritePrimitive.GetIndexBuffer()->Size(), m_SpritePrimitive.GetIndexBuffer()->GetDataType(), nullptr, entities.size());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void GizmoRenderer::RenderLine(const Entity *entity)
    {
    }
    void GizmoRenderer::RenderPoint(const Entity *entity)
    {
    }
    void GizmoRenderer::RenderQuad(const Entity *entity)
    {
    }
    void GizmoRenderer::RenderCircle(const Entity *entity)
    {
    }
    void GizmoRenderer::RenderLineInstances(const std::vector<Entity *> entities)
    {
    }
    void GizmoRenderer::RenderPointInstanced(const std::vector<Entity *> entities)
    {
    }
    void GizmoRenderer::RenderQuadInstanced(const std::vector<Entity *> entities)
    {
    }
    void GizmoRenderer::RenderCircleInstanced(const std::vector<Entity *> entities)
    {
    }

    void SceneRenderer::RenderGizmo(const Scene *scene)
    {
    }
    void SceneRenderer::Render(const Scene *scene)
    {
    }
    void SceneRenderer::RenderUI(const Scene *scene)
    {
    }
}