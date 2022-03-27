#include "SceneRenderer.h"

namespace mulberry
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
        mQuadPrimitive = std::make_unique<Primitive>(PrimitiveType::QUAD);
        mLinePrimitive = std::make_unique<Primitive>(PrimitiveType::LINE);
        mPointPrimitive = std::make_unique<Primitive>(PrimitiveType::POINT);
        mCirclePrimitive = std::make_unique<Primitive>(PrimitiveType::CIRCLE);

        auto vertShader = GL::ShaderModule(GL::VERTEX_SHADER, spriteVertShader);
        auto fragShader = GL::ShaderModule(GL::FRAGMENT_SHADER, spriteFragShader);
        mSpriteShaderProgram = std::make_unique<GL::ShaderProgram>();
        mSpriteShaderProgram->AttachShader(vertShader);
        mSpriteShaderProgram->AttachShader(fragShader);

        auto gVertShader = GL::ShaderModule(GL::VERTEX_SHADER, gizmoVertShader);
        auto gFragShader = GL::ShaderModule(GL::FRAGMENT_SHADER, gizmoFragShader);
        mGizmoShaderProgram = std::make_unique<GL::ShaderProgram>();
        mGizmoShaderProgram->AttachShader(gVertShader);
        mGizmoShaderProgram->AttachShader(gFragShader);
    }

    void SceneRenderer::RenderSprite(const Entity *entity)
    {
        auto transComp = entity->GetComponent<TransformComponent>();
        auto spriteComp = entity->GetComponent<SpriteComponent>();
        const GL::Texture *texture = spriteComp->GetTexture();
        if (texture == nullptr)
            return;
        
        //map to sprite size
        Mat4 mat=transComp->GetModelMat();
        mat*=Mat4::Scale(Vec2(texture->GetCreateInfo().data.width/2,texture->GetCreateInfo().data.height/2));

        mSpriteShaderProgram->SetUniformValue("modelMat", mat);
        texture->BindTo(mSpriteShaderProgram->GetUniform("sprite"), 0);
        mQuadPrimitive->Bind(mSpriteShaderProgram->GetAttribute("inPosition"), mSpriteShaderProgram->GetAttribute("inTexcoord"));
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mQuadPrimitive->GetIndexBuffer()->GetID());
        glDrawElements(GL_TRIANGLES, mQuadPrimitive->GetIndexBuffer()->Size(), mQuadPrimitive->GetIndexBuffer()->GetDataType(), nullptr);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        mQuadPrimitive->UnBind(mSpriteShaderProgram->GetAttribute("inPosition"), mSpriteShaderProgram->GetAttribute("inTexcoord"));
        texture->UnBindFrom(mSpriteShaderProgram->GetUniform("sprite"));
    }

    void SceneRenderer::RenderSpriteInstanced(const std::vector<const Entity *> spriteComps)
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mQuadPrimitive->GetIndexBuffer()->GetID());
        glDrawElementsInstanced(GL_TRIANGLES, mQuadPrimitive->GetIndexBuffer()->Size(), mQuadPrimitive->GetIndexBuffer()->GetDataType(), nullptr, spriteComps.size());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void SceneRenderer::RenderLine(const Entity *entity)
    {
        auto transComp = entity->GetComponent<TransformComponent>();
        auto spriteComp = entity->GetComponent<SpriteComponent>();
        const GL::Texture *texture = spriteComp->GetTexture();
        if (texture == nullptr)
            return;
        mGizmoShaderProgram->SetUniformValue("modelMat", transComp->GetModelMat());
        mLinePrimitive->Bind(mGizmoShaderProgram->GetAttribute("inPosition"));
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mLinePrimitive->GetIndexBuffer()->GetID());
        glDrawElements(GL_LINES, mLinePrimitive->GetIndexBuffer()->Size(), mLinePrimitive->GetIndexBuffer()->GetDataType(), nullptr);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        mLinePrimitive->UnBind(mGizmoShaderProgram->GetAttribute("inPosition"));
    }
    void SceneRenderer::RenderPoint(const Entity *entity)
    {
        auto transComp = entity->GetComponent<TransformComponent>();
        auto spriteComp = entity->GetComponent<SpriteComponent>();
        const GL::Texture *texture = spriteComp->GetTexture();
        if (texture == nullptr)
            return;
        mGizmoShaderProgram->SetUniformValue("modelMat", transComp->GetModelMat());
        mPointPrimitive->Bind(mGizmoShaderProgram->GetAttribute("inPosition"));
        glPointSize(5);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mPointPrimitive->GetIndexBuffer()->GetID());
        glDrawElements(GL_POINTS, mPointPrimitive->GetIndexBuffer()->Size(), mPointPrimitive->GetIndexBuffer()->GetDataType(), nullptr);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glPointSize(1);
        mPointPrimitive->UnBind(mGizmoShaderProgram->GetAttribute("inPosition"));
    }
    void SceneRenderer::RenderQuad(const Entity *entity)
    {
        auto transComp = entity->GetComponent<TransformComponent>();
        auto spriteComp = entity->GetComponent<SpriteComponent>();
        const GL::Texture *texture = spriteComp->GetTexture();
        if (texture == nullptr)
            return;
        mGizmoShaderProgram->SetUniformValue("modelMat", transComp->GetModelMat());
        mQuadPrimitive->Bind(mGizmoShaderProgram->GetAttribute("inPosition"));
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mQuadPrimitive->GetIndexBuffer()->GetID());
        glDrawArrays(GL_LINE_LOOP, 0, mQuadPrimitive->GetPosition().size());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        mQuadPrimitive->UnBind(mGizmoShaderProgram->GetAttribute("inPosition"));
    }
    void SceneRenderer::RenderCircle(const Entity *entity)
    {
        auto transComp = entity->GetComponent<TransformComponent>();
        auto spriteComp = entity->GetComponent<SpriteComponent>();
        const GL::Texture *texture = spriteComp->GetTexture();
        if (texture == nullptr)
            return;
        mGizmoShaderProgram->SetUniformValue("modelMat", transComp->GetModelMat());
        mCirclePrimitive->Bind(mGizmoShaderProgram->GetAttribute("inPosition"));
        glPointSize(5);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mCirclePrimitive->GetIndexBuffer()->GetID());
        glDrawArrays(GL_LINE_LOOP, 0, mCirclePrimitive->GetPosition().size());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glPointSize(1);
        mCirclePrimitive->UnBind(mGizmoShaderProgram->GetAttribute("inPosition"));
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
        for (const auto &entity : scene->mEntities)
        {
            CameraComponent *camera = entity->GetComponent<CameraComponent>();
            if (camera)
                cameraComponents.emplace_back(camera);
        }
        std::vector<const Entity *> entitiesWithSpriteComp;
        for (const auto &entity : scene->mEntities)
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
            mSpriteShaderProgram->SetActive(true);
            mSpriteShaderProgram->SetUniformValue("viewMat", viewMat);
            mSpriteShaderProgram->SetUniformValue("projMat", projMat);
            for (const auto &entity : entitiesWithSpriteComp)
                RenderSprite(entity);
            mSpriteShaderProgram->SetActive(false);
        }
    }
}