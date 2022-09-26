#include "SceneRenderer.h"
#include "GL/Renderer.h"
namespace mulberry
{
    const std::string spriteVertShader = "#version 330 core\n"
                                         "out vec2 fragTexcoord;\n"
                                         "in vec2 inPosition;\n"
                                         "in vec2 inTexcoord;\n"
                                         "uniform mat4 modelMat;\n"
                                         "uniform mat4 viewMat;\n"
                                         "uniform mat4 projMat;\n"
                                         "void main()\n"
                                         "{\n"
                                         "	gl_Position=projMat*viewMat*modelMat*vec4(inPosition,0.0,1.0);\n"
                                         "	fragTexcoord=inTexcoord;\n"
                                         "}";

    const std::string spriteFragShader = "#version 330 core\n"
                                         "out vec4 outColor;\n"
                                         "in vec2 fragTexcoord;\n"
                                         "uniform sampler2D sprite;\n"
                                         "void main()\n"
                                         "{\n"
                                         "	outColor=texture(sprite,fragTexcoord);\n"
                                         "}";

    const std::string gizmoVertShader = "#version 330 core\n"
                                        "in vec2 inPosition;\n"
                                        "uniform mat4 modelMat;\n"
                                        "uniform mat4 viewMat;\n"
                                        "uniform mat4 projMat;\n"
                                        "void main()\n"
                                        "{\n"
                                        "	gl_Position=projMat*viewMat*modelMat*vec4(inPosition,0.0,1.0);\n"
                                        "}";

    const std::string gizmoFragShader = "#version 330 core\n"
                                        "out vec4 outColor;\n"
                                        "void main()\n"
                                        "{\n"
                                        "	outColor=vec4(0.0,1.0,0.0,1.0);\n"
                                        "}";

    void SceneRenderer::Init()
    {
        mQuadPrimitive = std::make_unique<Primitive>(PrimitiveType::QUAD);
        mSpritePrimitive = std::make_unique<Primitive>(PrimitiveType::SPRITE);
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

    void SceneRenderer::RenderSprite(const Entity *entity, CameraComponent *camera)
    {
        auto transComp = entity->GetComponent<TransformComponent>();
        auto spriteComp = entity->GetComponent<SpriteComponent>();
        const GL::Texture *texture = spriteComp->GetTexture();
        if (texture == nullptr)
            return;

        //map to sprite size
        Mat4 mat = transComp->GetModelMat();
        mat *= Mat4::Scale(Vec2(texture->GetCreateInfo().data.width / 2, texture->GetCreateInfo().data.height / 2));

        mSpriteShaderProgram->SetActive(true);
        mSpriteShaderProgram->SetUniformValue("modelMat", mat);
        mSpriteShaderProgram->SetUniformValue("viewMat", camera->GetViewMat());
        mSpriteShaderProgram->SetUniformValue("projMat", camera->GetProjMat());
        texture->BindTo(mSpriteShaderProgram->GetUniform("sprite"), 0);
        mSpritePrimitive->Bind(mSpriteShaderProgram->GetAttribute("inPosition"), mSpriteShaderProgram->GetAttribute("inTexcoord"));

        GL::Renderer::Render(mSpritePrimitive->GetIndexBuffer(), GL::TRIANGLES);

        mSpritePrimitive->UnBind(mSpriteShaderProgram->GetAttribute("inPosition"), mSpriteShaderProgram->GetAttribute("inTexcoord"));
        texture->UnBindFrom(mSpriteShaderProgram->GetUniform("sprite"));
        mSpriteShaderProgram->SetActive(false);
    }

    void SceneRenderer::RenderSpriteInstanced(const std::vector<const Entity *> spriteComps, CameraComponent *camera)
    {
        GL::Renderer::RenderInstanced(mSpritePrimitive->GetIndexBuffer(), GL::TRIANGLES, spriteComps.size());
    }

    void SceneRenderer::RenderLine(const Entity *entity, CameraComponent *camera)
    {
        auto transComp = entity->GetComponent<TransformComponent>();
        auto spriteComp = entity->GetComponent<SpriteComponent>();
        const GL::Texture *texture = spriteComp->GetTexture();
        if (texture == nullptr)
            return;
        mGizmoShaderProgram->SetUniformValue("modelMat", transComp->GetModelMat());
        mLinePrimitive->Bind(mGizmoShaderProgram->GetAttribute("inPosition"));
        GL::Renderer::Render(mLinePrimitive->GetIndexBuffer(), GL::LINES);
        mLinePrimitive->UnBind(mGizmoShaderProgram->GetAttribute("inPosition"));
    }
    void SceneRenderer::RenderPoint(const Entity *entity, CameraComponent *camera)
    {
        auto transComp = entity->GetComponent<TransformComponent>();
        auto spriteComp = entity->GetComponent<SpriteComponent>();
        const GL::Texture *texture = spriteComp->GetTexture();
        if (texture == nullptr)
            return;
        mGizmoShaderProgram->SetUniformValue("modelMat", transComp->GetModelMat());
        mPointPrimitive->Bind(mGizmoShaderProgram->GetAttribute("inPosition"));
        glPointSize(5);
        GL::Renderer::Render(mPointPrimitive->GetIndexBuffer(), GL::POINTS);
        glPointSize(1);
        mPointPrimitive->UnBind(mGizmoShaderProgram->GetAttribute("inPosition"));
    }
    void SceneRenderer::RenderQuad(const Entity *entity, CameraComponent *camera)
    {
        auto transComp = entity->GetComponent<TransformComponent>();
        auto spriteComp = entity->GetComponent<SpriteComponent>();
        const GL::Texture *texture = spriteComp->GetTexture();
        if (texture == nullptr)
            return;

        //map to sprite size
        Mat4 mat = transComp->GetModelMat();
        mat *= Mat4::Scale(Vec2(texture->GetCreateInfo().data.width / 2, texture->GetCreateInfo().data.height / 2));

        mGizmoShaderProgram->SetActive(true);
        mGizmoShaderProgram->SetUniformValue("modelMat", mat);
        mGizmoShaderProgram->SetUniformValue("viewMat", camera->GetViewMat());
        mGizmoShaderProgram->SetUniformValue("projMat", camera->GetProjMat());
        mQuadPrimitive->Bind(mGizmoShaderProgram->GetAttribute("inPosition"));
        GL::Renderer::Render(mQuadPrimitive->GetIndexBuffer(), GL::LINES);
        mQuadPrimitive->UnBind(mGizmoShaderProgram->GetAttribute("inPosition"));
        mGizmoShaderProgram->SetActive(false);
    }
    void SceneRenderer::RenderCircle(const Entity *entity, CameraComponent *camera)
    {
        auto transComp = entity->GetComponent<TransformComponent>();
        auto spriteComp = entity->GetComponent<SpriteComponent>();
        const GL::Texture *texture = spriteComp->GetTexture();
        if (texture == nullptr)
            return;

        Mat4 mat = transComp->GetModelMat();
        mat *= Mat4::Scale(Vec2(texture->GetCreateInfo().data.width / 2, texture->GetCreateInfo().data.height / 2));

        mGizmoShaderProgram->SetActive(true);
        mGizmoShaderProgram->SetUniformValue("modelMat", mat);
        mGizmoShaderProgram->SetUniformValue("viewMat", camera->GetViewMat());
        mGizmoShaderProgram->SetUniformValue("projMat", camera->GetProjMat());
        mCirclePrimitive->Bind(mGizmoShaderProgram->GetAttribute("inPosition"));
        GL::Renderer::Render(mCirclePrimitive->GetIndexBuffer(), GL::LINE_LOOP);
        mCirclePrimitive->UnBind(mGizmoShaderProgram->GetAttribute("inPosition"));
        mGizmoShaderProgram->SetActive(false);
    }

    void SceneRenderer::RenderLineInstances(const std::vector<const Entity *> entities, CameraComponent *camera)
    {
    }
    void SceneRenderer::RenderPointInstanced(const std::vector<const Entity *> entities, CameraComponent *camera)
    {
    }
    void SceneRenderer::RenderQuadInstanced(const std::vector<const Entity *> entities, CameraComponent *camera)
    {
    }
    void SceneRenderer::RenderCircleInstanced(const std::vector<const Entity *> entities, CameraComponent *camera)
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
            Color clearColor = camera->GetClearColor();

            glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
            glClear(GL_COLOR_BUFFER_BIT);

            glDisable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            //render sprite
            for (const auto &entity : entitiesWithSpriteComp)
                RenderSprite(entity, camera);
        }
    }
}