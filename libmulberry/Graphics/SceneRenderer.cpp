#include "SceneRenderer.h"
#include "GL/Renderer.h"
namespace mulberry
{
    void SceneRenderer::Init()
    {
        mGizmoMaterial = std::make_unique<GizmoMaterial>();

        mQuadPrimitive = std::make_unique<Primitive>(PrimitiveType::QUAD);
        mSpritePrimitive = std::make_unique<Primitive>(PrimitiveType::SPRITE);
        mLinePrimitive = std::make_unique<Primitive>(PrimitiveType::LINE);
        mPointPrimitive = std::make_unique<Primitive>(PrimitiveType::POINT);
        mCirclePrimitive = std::make_unique<Primitive>(PrimitiveType::CIRCLE);
    }

    void SceneRenderer::RenderSprite(const Entity *entity, CameraComponent *camera)
    {
        auto transComp = entity->GetComponent<TransformComponent>();
        auto spriteComp = entity->GetComponent<RenderComponent>();
        const SpriteMaterial *material = (SpriteMaterial*)spriteComp->GetMaterial();

        // map to sprite size
        Mat4 mat = transComp->GetModelMat();
        mat *= Mat4::Scale(Vec2(material->GetSprite()->GetCreateInfo().data.width / 2, material->GetSprite()->GetCreateInfo().data.height / 2));

        material->shaderProgram->SetActive(true);
        material->shaderProgram->SetUniformValue("modelMat", mat);
        material->shaderProgram->SetUniformValue("viewMat", camera->GetViewMat());
        material->shaderProgram->SetUniformValue("projMat", camera->GetProjMat());
        material->SetUniformValue();
        mSpritePrimitive->Bind(material->shaderProgram->GetAttribute("inPosition"), material->shaderProgram->GetAttribute("inTexcoord"));

        GL::Renderer::Render(mSpritePrimitive->GetIndexBuffer(), GL::TRIANGLES);

        mSpritePrimitive->UnBind(material->shaderProgram->GetAttribute("inPosition"), material->shaderProgram->GetAttribute("inTexcoord"));
        material->GetSprite()->UnBindFrom(material->shaderProgram->GetUniform("sprite"));
        material->shaderProgram->SetActive(false);
    }

    void SceneRenderer::RenderSpriteInstanced(const std::vector<const Entity *> spriteComps, CameraComponent *camera)
    {
        GL::Renderer::RenderInstanced(mSpritePrimitive->GetIndexBuffer(), GL::TRIANGLES, spriteComps.size());
    }

    void SceneRenderer::RenderLine(const Entity *entity, CameraComponent *camera)
    {
        auto transComp = entity->GetComponent<TransformComponent>();
        auto spriteComp = entity->GetComponent<RenderComponent>();
        mGizmoMaterial->shaderProgram->SetUniformValue("modelMat", transComp->GetModelMat());
        mLinePrimitive->Bind(mGizmoMaterial->shaderProgram->GetAttribute("inPosition"));
        GL::Renderer::Render(mLinePrimitive->GetIndexBuffer(), GL::LINES);
        mLinePrimitive->UnBind(mGizmoMaterial->shaderProgram->GetAttribute("inPosition"));
    }
    void SceneRenderer::RenderPoint(const Entity *entity, CameraComponent *camera)
    {
        auto transComp = entity->GetComponent<TransformComponent>();
        auto spriteComp = entity->GetComponent<RenderComponent>();
        mGizmoMaterial->shaderProgram->SetUniformValue("modelMat", transComp->GetModelMat());
        mPointPrimitive->Bind(mGizmoMaterial->shaderProgram->GetAttribute("inPosition"));
        glPointSize(5);
        GL::Renderer::Render(mPointPrimitive->GetIndexBuffer(), GL::POINTS);
        glPointSize(1);
        mPointPrimitive->UnBind(mGizmoMaterial->shaderProgram->GetAttribute("inPosition"));
    }
    void SceneRenderer::RenderQuad(const Entity *entity, CameraComponent *camera)
    {
        auto transComp = entity->GetComponent<TransformComponent>();
        auto spriteComp = entity->GetComponent<RenderComponent>();
        const SpriteMaterial *material = (SpriteMaterial *)spriteComp->GetMaterial();

        // map to sprite size
        Mat4 mat = transComp->GetModelMat();
        mat *= Mat4::Scale(Vec2(material->GetSprite()->GetCreateInfo().data.width / 2, material->GetSprite()->GetCreateInfo().data.height / 2));

        mGizmoMaterial->shaderProgram->SetActive(true);
        mGizmoMaterial->shaderProgram->SetUniformValue("modelMat", mat);
        mGizmoMaterial->shaderProgram->SetUniformValue("viewMat", camera->GetViewMat());
        mGizmoMaterial->shaderProgram->SetUniformValue("projMat", camera->GetProjMat());
        mQuadPrimitive->Bind(mGizmoMaterial->shaderProgram->GetAttribute("inPosition"));
        GL::Renderer::Render(mQuadPrimitive->GetIndexBuffer(), GL::LINES);
        mQuadPrimitive->UnBind(mGizmoMaterial->shaderProgram->GetAttribute("inPosition"));
        mGizmoMaterial->shaderProgram->SetActive(false);
    }
    void SceneRenderer::RenderCircle(const Entity *entity, CameraComponent *camera)
    {
        auto transComp = entity->GetComponent<TransformComponent>();
        auto spriteComp = entity->GetComponent<RenderComponent>();
        const SpriteMaterial *material = (SpriteMaterial *)spriteComp->GetMaterial();

        // map to sprite size
        Mat4 mat = transComp->GetModelMat();
        mat *= Mat4::Scale(Vec2(material->GetSprite()->GetCreateInfo().data.width / 2, material->GetSprite()->GetCreateInfo().data.height / 2));

        mGizmoMaterial->shaderProgram->SetActive(true);
        mGizmoMaterial->shaderProgram->SetUniformValue("modelMat", mat);
        mGizmoMaterial->shaderProgram->SetUniformValue("viewMat", camera->GetViewMat());
        mGizmoMaterial->shaderProgram->SetUniformValue("projMat", camera->GetProjMat());
        mCirclePrimitive->Bind(mGizmoMaterial->shaderProgram->GetAttribute("inPosition"));
        GL::Renderer::Render(mCirclePrimitive->GetIndexBuffer(), GL::LINE_LOOP);
        mCirclePrimitive->UnBind(mGizmoMaterial->shaderProgram->GetAttribute("inPosition"));
        mGizmoMaterial->shaderProgram->SetActive(false);
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
            if (entity->GetComponent<RenderComponent>() != nullptr)
                entitiesWithSpriteComp.emplace_back(entity.get());
        }
        for (auto camera : cameraComponents)
        {
            Color clearColor = camera->GetClearColor();
            GL::Renderer::ClearColorBuffer(clearColor.r, clearColor.g, clearColor.b, clearColor.a);

            glDisable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            // render sprite
            for (const auto &entity : entitiesWithSpriteComp)
                RenderSprite(entity, camera);
        }
    }
}