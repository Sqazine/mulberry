#include "Renderer.h"

namespace Pe2
{
    const std::string spriteVertShader = "#version 430 core\n"
                                         "layout(location=0) out vec2 fragTexcoord;\n"
                                         "layout(location=0) in vec2 inPosition;\n"
                                         "layout(location=1) in vec2 inTexcoord;\n"
                                         "uniform mat4 modelMat;\n"
                                         "uniform mat4 viewMat;\n"
                                         "uniform mat4 projMat;\n"
                                         "void main()\n"
                                         "{\n"
                                         "	gl_Position=projMat*viewMat*modelMat*vec4(inPosition,0.0,1.0);\n"
                                         "	fragTexcoord=inTexcoord;\n"
                                         "}";

    const std::string spriteFragShader = "#version 430 core\n"
                                         "layout(location=0) out vec4 outColor;\n"
                                         "layout(location=0) in vec2 fragTexcoord;\n"
                                         "layout(binding=0) uniform sampler2D sprite;\n"
                                         "void main()\n"
                                         "{\n"
                                         "	outColor=texture(sprite,fragTexcoord);\n"
                                         "}";

    const std::string gizmoVertShader = "#version 430 core\n"
                                        "layout(location=0) in vec2 inPosition;\n"
                                        "uniform mat4 modelMat;\n"
                                        "uniform mat4 viewMat;\n"
                                        "uniform mat4 projMat;\n"
                                        "void main()\n"
                                        "{\n"
                                        "	gl_Position=projMat*viewMat*modelMat*vec4(inPosition,0.0,1.0);\n"
                                        "}";

    const std::string gizmoFragShader = "#version 430 core\n"
                                        "layout(location=0) out vec4 outColor;\n"
                                        "void main()\n"
                                        "{\n"
                                        "	outColor=vec4(0.0,1.0,0.0,1.0);\n"
                                        "}";

    void SceneRenderer::Init()
    {
        m_QuadPrimitive = std::make_unique<Primitive>(PrimitiveType::QUAD);
        m_LinePrimitive = std::make_unique<Primitive>(PrimitiveType::LINE);
        m_PointPrimitive = std::make_unique<Primitive>(PrimitiveType::POINT);
        m_CirclePrimitive = std::make_unique<Primitive>(PrimitiveType::CIRCLE);

        auto vertShader = ShaderModule(VERTEX_SHADER, spriteVertShader);
        auto fragShader = ShaderModule(FRAGMENT_SHADER, spriteFragShader);
        m_SpriteShaderProgram = std::make_unique<ShaderProgram>();
        m_SpriteShaderProgram->AttachShader(vertShader);
        m_SpriteShaderProgram->AttachShader(fragShader);

        auto gVertShader = ShaderModule(VERTEX_SHADER, gizmoVertShader);
        auto gFragShader = ShaderModule(FRAGMENT_SHADER, gizmoFragShader);
        m_GizmoShaderProgram = std::make_unique<ShaderProgram>();
        m_GizmoShaderProgram->AttachShader(gVertShader);
        m_GizmoShaderProgram->AttachShader(gFragShader);
    }

    void SceneRenderer::RenderSprite(const Entity *entity)
    {
        auto transComp = entity->GetComponent<TransformComponent>();
        auto spriteComp = entity->GetComponent<SpriteComponent>();
        const Texture *texture = spriteComp->GetTexture();
        if (texture == nullptr)
            return;
        
        //map to sprite size
        Mat4 mat=transComp->GetModelMat();
        mat*=Mat4::Scale(Vec2(texture->GetCreateInfo().data.width/2,texture->GetCreateInfo().data.height/2));

        m_SpriteShaderProgram->SetUniformValue("modelMat", mat);
        texture->BindTo(m_SpriteShaderProgram->GetUniform("sprite"), 0);
        m_QuadPrimitive->Bind(m_SpriteShaderProgram->GetAttribute("inPosition"), m_SpriteShaderProgram->GetAttribute("inTexcoord"));
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_QuadPrimitive->GetIndexBuffer()->GetID());
        glDrawElements(GL_TRIANGLES, m_QuadPrimitive->GetIndexBuffer()->Size(), m_QuadPrimitive->GetIndexBuffer()->GetDataType(), nullptr);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        m_QuadPrimitive->UnBind(m_SpriteShaderProgram->GetAttribute("inPosition"), m_SpriteShaderProgram->GetAttribute("inTexcoord"));
        texture->UnBindFrom(m_SpriteShaderProgram->GetUniform("sprite"));
    }

    void SceneRenderer::RenderSpriteInstanced(const std::vector<const Entity *> spriteComps)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_QuadPrimitive->GetIndexBuffer()->GetID());
        glDrawElementsInstanced(GL_TRIANGLES, m_QuadPrimitive->GetIndexBuffer()->Size(), m_QuadPrimitive->GetIndexBuffer()->GetDataType(), nullptr, spriteComps.size());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void SceneRenderer::RenderLine(const Entity *entity)
    {
        auto transComp = entity->GetComponent<TransformComponent>();
        auto spriteComp = entity->GetComponent<SpriteComponent>();
        const Texture *texture = spriteComp->GetTexture();
        if (texture == nullptr)
            return;
        m_GizmoShaderProgram->SetUniformValue("modelMat", transComp->GetModelMat());
        m_LinePrimitive->Bind(m_GizmoShaderProgram->GetAttribute("inPosition"));
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_LinePrimitive->GetIndexBuffer()->GetID());
        glDrawElements(GL_LINES, m_LinePrimitive->GetIndexBuffer()->Size(), m_LinePrimitive->GetIndexBuffer()->GetDataType(), nullptr);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        m_LinePrimitive->UnBind(m_GizmoShaderProgram->GetAttribute("inPosition"));
    }
    void SceneRenderer::RenderPoint(const Entity *entity)
    {
        auto transComp = entity->GetComponent<TransformComponent>();
        auto spriteComp = entity->GetComponent<SpriteComponent>();
        const Texture *texture = spriteComp->GetTexture();
        if (texture == nullptr)
            return;
        m_GizmoShaderProgram->SetUniformValue("modelMat", transComp->GetModelMat());
        m_PointPrimitive->Bind(m_GizmoShaderProgram->GetAttribute("inPosition"));
        glPointSize(5);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_PointPrimitive->GetIndexBuffer()->GetID());
        glDrawElements(GL_POINTS, m_PointPrimitive->GetIndexBuffer()->Size(), m_PointPrimitive->GetIndexBuffer()->GetDataType(), nullptr);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glPointSize(1);
        m_PointPrimitive->UnBind(m_GizmoShaderProgram->GetAttribute("inPosition"));
    }
    void SceneRenderer::RenderQuad(const Entity *entity)
    {
        auto transComp = entity->GetComponent<TransformComponent>();
        auto spriteComp = entity->GetComponent<SpriteComponent>();
        const Texture *texture = spriteComp->GetTexture();
        if (texture == nullptr)
            return;
        m_GizmoShaderProgram->SetUniformValue("modelMat", transComp->GetModelMat());
        m_QuadPrimitive->Bind(m_GizmoShaderProgram->GetAttribute("inPosition"));
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_QuadPrimitive->GetIndexBuffer()->GetID());
        glDrawArrays(GL_LINE_LOOP, 0, m_QuadPrimitive->GetPosition().size());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        m_QuadPrimitive->UnBind(m_GizmoShaderProgram->GetAttribute("inPosition"));
    }
    void SceneRenderer::RenderCircle(const Entity *entity)
    {
        auto transComp = entity->GetComponent<TransformComponent>();
        auto spriteComp = entity->GetComponent<SpriteComponent>();
        const Texture *texture = spriteComp->GetTexture();
        if (texture == nullptr)
            return;
        m_GizmoShaderProgram->SetUniformValue("modelMat", transComp->GetModelMat());
        m_CirclePrimitive->Bind(m_GizmoShaderProgram->GetAttribute("inPosition"));
        glPointSize(5);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_CirclePrimitive->GetIndexBuffer()->GetID());
        glDrawArrays(GL_LINE_LOOP, 0, m_CirclePrimitive->GetPosition().size());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glPointSize(1);
        m_CirclePrimitive->UnBind(m_GizmoShaderProgram->GetAttribute("inPosition"));
    }

    void SceneRenderer::RenderLineInstances(const std::vector<const Entity *> entities)
    {
    }
    void SceneRenderer::RenderPointInstanced(const std::vector<const Entity *> entities)
    {
    }
    void SceneRenderer::RenderQuadInstanced(const std::vector<const Entity *> entities)
    {
    }
    void SceneRenderer::RenderCircleInstanced(const std::vector<const Entity *> entities)
    {
    }

    void SceneRenderer::Render(const Scene *scene)
    {
        std::vector<CameraComponent *> cameraComponents;
        for (const auto &entity : scene->m_Entities)
        {
            CameraComponent *camera = entity->GetComponent<CameraComponent>();
            if (camera)
                cameraComponents.emplace_back(camera);
        }
        std::vector<const Entity *> entitiesWithSpriteComp;
        for (const auto &entity : scene->m_Entities)
        {
            if (entity->GetComponent<SpriteComponent>() != nullptr)
                entitiesWithSpriteComp.emplace_back(entity.get());
        }
        for (auto camera : cameraComponents)
        {
            Mat4 viewMat = camera->GetViewMat();
            Mat4 projMat = camera->GetProjMat();

            Color clearColor = camera->GetClearColor();

            glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
            glClear(GL_COLOR_BUFFER_BIT);

            glDisable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            //render sprite
            m_SpriteShaderProgram->SetActive(true);
            m_SpriteShaderProgram->SetUniformValue("viewMat", viewMat);
            m_SpriteShaderProgram->SetUniformValue("projMat", projMat);
            for (const auto &entity : entitiesWithSpriteComp)
                RenderSprite(entity);
            m_SpriteShaderProgram->SetActive(false);
        }
    }
}