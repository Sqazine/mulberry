#include "SceneRenderer.h"
#include "GL/Renderer.h"
namespace mulberry
{
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
        const SpriteMaterial *material = (SpriteMaterial *)spriteComp->material.get();

        //map to sprite size
        Mat4 mat = transComp->GetModelMat();
        mat *= Mat4::Scale(Vec2(material->spriteTexture->GetCreateInfo().data.width / 2, material->spriteTexture->GetCreateInfo().data.height / 2));

        material->shaderProgram->SetActive(true);
        material->shaderProgram->SetUniformValue("modelMat", mat);
        material->shaderProgram->SetUniformValue("viewMat", camera->GetViewMat());
        material->shaderProgram->SetUniformValue("projMat", camera->GetProjMat());
        material->spriteTexture->BindTo(material->shaderProgram->GetUniform("sprite"), 0);
        mSpritePrimitive->Bind(material->shaderProgram->GetAttribute("inPosition"), material->shaderProgram->GetAttribute("inTexcoord"));

        GL::Renderer::Render(mSpritePrimitive->GetIndexBuffer(), GL::TRIANGLES);

        mSpritePrimitive->UnBind(material->shaderProgram->GetAttribute("inPosition"), material->shaderProgram->GetAttribute("inTexcoord"));
        material->spriteTexture->UnBindFrom(material->shaderProgram->GetUniform("sprite"));
        material->shaderProgram->SetActive(false);
    }

    void SceneRenderer::RenderSpriteInstanced(const std::vector<const Entity *> spriteComps, CameraComponent *camera)
    {
        GL::Renderer::RenderInstanced(mSpritePrimitive->GetIndexBuffer(), GL::TRIANGLES, spriteComps.size());
    }

    void SceneRenderer::RenderLine(const Entity *entity, CameraComponent *camera)
    {
        auto transComp = entity->GetComponent<TransformComponent>();
        auto spriteComp = entity->GetComponent<SpriteComponent>();
        mGizmoShaderProgram->SetUniformValue("modelMat", transComp->GetModelMat());
        mLinePrimitive->Bind(mGizmoShaderProgram->GetAttribute("inPosition"));
        GL::Renderer::Render(mLinePrimitive->GetIndexBuffer(), GL::LINES);
        mLinePrimitive->UnBind(mGizmoShaderProgram->GetAttribute("inPosition"));
    }
    void SceneRenderer::RenderPoint(const Entity *entity, CameraComponent *camera)
    {
        auto transComp = entity->GetComponent<TransformComponent>();
        auto spriteComp = entity->GetComponent<SpriteComponent>();
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
        const SpriteMaterial *material = (SpriteMaterial *)spriteComp->material.get();

        //map to sprite size
        Mat4 mat = transComp->GetModelMat();
        mat *= Mat4::Scale(Vec2(material->spriteTexture->GetCreateInfo().data.width / 2, material->spriteTexture->GetCreateInfo().data.height / 2));

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
        const SpriteMaterial *material = (SpriteMaterial *)spriteComp->material.get();

        //map to sprite size
        Mat4 mat = transComp->GetModelMat();
        mat *= Mat4::Scale(Vec2(material->spriteTexture->GetCreateInfo().data.width / 2, material->spriteTexture->GetCreateInfo().data.height / 2));

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