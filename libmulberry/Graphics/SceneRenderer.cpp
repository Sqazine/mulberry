#include "SceneRenderer.h"
#include "GL/Renderer.h"
#include "App.h"
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
        auto spriteComp = entity->GetComponent<SpriteComponent>();
        const SpriteMaterial *material = (SpriteMaterial *)spriteComp->GetMaterial();

        // map to sprite size
        Mat4 mat = transComp->GetModelMat();
        mat *= Mat4::Scale(Vec2(material->GetSprite()->GetCreateInfo().data.width / 2, material->GetSprite()->GetCreateInfo().data.height / 2));

        material->GetShaderProgram()->SetActive(true);
        material->GetShaderProgram()->SetUniformValue("modelMat", mat);
        material->GetShaderProgram()->SetUniformValue("viewMat", camera->GetViewMat());
        material->GetShaderProgram()->SetUniformValue("projMat", camera->GetProjMat());
        material->SetUniformValue();
        mSpritePrimitive->Bind(material->GetShaderProgram()->GetAttribute("inPosition"), material->GetShaderProgram()->GetAttribute("inTexcoord"));

        gl::Renderer::Render(mSpritePrimitive->GetIndexBuffer(), gl::TRIANGLES);

        mSpritePrimitive->UnBind(material->GetShaderProgram()->GetAttribute("inPosition"), material->GetShaderProgram()->GetAttribute("inTexcoord"));
        material->ResetUniformValue();
        material->GetShaderProgram()->SetActive(false);
    }

    void SceneRenderer::RenderSpriteInstanced(const std::vector<const Entity *> spriteComps, CameraComponent *camera)
    {
        gl::Renderer::RenderInstanced(mSpritePrimitive->GetIndexBuffer(), gl::TRIANGLES, spriteComps.size());
    }

    void SceneRenderer::RenderLine(const Entity *entity, CameraComponent *camera)
    {
        auto transComp = entity->GetComponent<TransformComponent>();
        auto spriteComp = entity->GetComponent<RenderComponent>();
        mGizmoMaterial->GetShaderProgram()->SetUniformValue("modelMat", transComp->GetModelMat());
        mLinePrimitive->Bind(mGizmoMaterial->GetShaderProgram()->GetAttribute("inPosition"));
        gl::Renderer::Render(mLinePrimitive->GetIndexBuffer(), gl::LINES);
        mLinePrimitive->UnBind(mGizmoMaterial->GetShaderProgram()->GetAttribute("inPosition"));
    }
    void SceneRenderer::RenderPoint(const Entity *entity, CameraComponent *camera)
    {
        auto transComp = entity->GetComponent<TransformComponent>();
        auto spriteComp = entity->GetComponent<RenderComponent>();
        mGizmoMaterial->GetShaderProgram()->SetUniformValue("modelMat", transComp->GetModelMat());
        mPointPrimitive->Bind(mGizmoMaterial->GetShaderProgram()->GetAttribute("inPosition"));
        glPointSize(5);
        gl::Renderer::Render(mPointPrimitive->GetIndexBuffer(), gl::POINTS);
        glPointSize(1);
        mPointPrimitive->UnBind(mGizmoMaterial->GetShaderProgram()->GetAttribute("inPosition"));
    }
    void SceneRenderer::RenderQuad(const Entity *entity, CameraComponent *camera)
    {
        auto transComp = entity->GetComponent<TransformComponent>();
        auto spriteComp = entity->GetComponent<SpriteComponent>();
        const SpriteMaterial *material = (SpriteMaterial *)spriteComp->GetMaterial();

        // map to sprite size
        Mat4 mat = transComp->GetModelMat();
        mat *= Mat4::Scale(Vec2(material->GetSprite()->GetCreateInfo().data.width / 2, material->GetSprite()->GetCreateInfo().data.height / 2));

        mGizmoMaterial->GetShaderProgram()->SetActive(true);
        mGizmoMaterial->GetShaderProgram()->SetUniformValue("modelMat", mat);
        mGizmoMaterial->GetShaderProgram()->SetUniformValue("viewMat", camera->GetViewMat());
        mGizmoMaterial->GetShaderProgram()->SetUniformValue("projMat", camera->GetProjMat());
        mQuadPrimitive->Bind(mGizmoMaterial->GetShaderProgram()->GetAttribute("inPosition"));
        gl::Renderer::Render(mQuadPrimitive->GetIndexBuffer(), gl::LINES);
        mQuadPrimitive->UnBind(mGizmoMaterial->GetShaderProgram()->GetAttribute("inPosition"));
        mGizmoMaterial->GetShaderProgram()->SetActive(false);
    }
    void SceneRenderer::RenderCircle(const Entity *entity, CameraComponent *camera)
    {
        auto transComp = entity->GetComponent<TransformComponent>();
        auto spriteComp = entity->GetComponent<RenderComponent>();
        const SpriteMaterial *material = (SpriteMaterial *)spriteComp->GetMaterial();

        // map to sprite size
        Mat4 mat = transComp->GetModelMat();
        mat *= Mat4::Scale(Vec2(material->GetSprite()->GetCreateInfo().data.width / 2, material->GetSprite()->GetCreateInfo().data.height / 2));

        mGizmoMaterial->GetShaderProgram()->SetActive(true);
        mGizmoMaterial->GetShaderProgram()->SetUniformValue("modelMat", mat);
        mGizmoMaterial->GetShaderProgram()->SetUniformValue("viewMat", camera->GetViewMat());
        mGizmoMaterial->GetShaderProgram()->SetUniformValue("projMat", camera->GetProjMat());
        mCirclePrimitive->Bind(mGizmoMaterial->GetShaderProgram()->GetAttribute("inPosition"));
        gl::Renderer::Render(mCirclePrimitive->GetIndexBuffer(), gl::LINE_LOOP);
        mCirclePrimitive->UnBind(mGizmoMaterial->GetShaderProgram()->GetAttribute("inPosition"));
        mGizmoMaterial->GetShaderProgram()->SetActive(false);
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
            gl::Renderer::SetViewport(App::GetInstance().GetWindow()->GetViewportInfo());

            Color clearColor = camera->GetClearColor();
            gl::Renderer::ClearColorBuffer(clearColor.r, clearColor.g, clearColor.b, clearColor.a);

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