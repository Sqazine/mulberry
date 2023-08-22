#include "SceneRenderer.h"
#include "RasterPipeline.h"
#include "App.h"
#include "RenderMaterial.h"
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

        mRasterPipeline = std::make_unique<RasterPipeline>();
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

        material->GetShaderProgram()->SetVertexArray(mSpritePrimitive->GetVertexArray());

        material->GetShaderProgram()->SetVertexBuffer("inPosition", mSpritePrimitive->GetPositionBuffer());
        material->GetShaderProgram()->SetVertexBuffer("inTexcoord", mSpritePrimitive->GetTexcoordBuffer());

        mRasterPipeline->Render(*mSpritePrimitive, PrimitiveRenderType::TRIANGLE_LIST);

        material->GetShaderProgram()->ResetVertexBuffer("inTexcoord");
        material->GetShaderProgram()->ResetVertexBuffer("inPosition");

        material->GetShaderProgram()->ResetVertexArray();

        material->ResetUniformValue();

        material->GetShaderProgram()->SetActive(false);
    }

    void SceneRenderer::RenderSpriteInstanced(const std::vector<const Entity *> spriteComps, CameraComponent *camera)
    {
        mRasterPipeline->RenderInstanced(*mSpritePrimitive, PrimitiveRenderType::LINE_LIST, spriteComps.size());
    }

    void SceneRenderer::RenderLine(const Entity *entity, CameraComponent *camera)
    {
        auto transComp = entity->GetComponent<TransformComponent>();
        auto spriteComp = entity->GetComponent<RenderComponent>();

        mGizmoMaterial->GetShaderProgram()->SetActive(true);

        mGizmoMaterial->GetShaderProgram()->SetUniformValue("modelMat", transComp->GetModelMat());
        mGizmoMaterial->GetShaderProgram()->SetUniformValue("viewMat", camera->GetViewMat());
        mGizmoMaterial->GetShaderProgram()->SetUniformValue("projMat", camera->GetProjMat());

        mGizmoMaterial->SetUniformValue();

        mGizmoMaterial->GetShaderProgram()->SetVertexArray(mLinePrimitive->GetVertexArray());

        mGizmoMaterial->GetShaderProgram()->SetVertexBuffer("inPosition", mLinePrimitive->GetPositionBuffer());

        mRasterPipeline->Render(*mLinePrimitive, PrimitiveRenderType::LINE_LIST);

        mGizmoMaterial->GetShaderProgram()->ResetVertexBuffer("inPosition");

        mGizmoMaterial->ResetUniformValue();

        mGizmoMaterial->GetShaderProgram()->ResetVertexArray();

        mGizmoMaterial->GetShaderProgram()->SetActive(false);
    }
    void SceneRenderer::RenderPoint(const Entity *entity, CameraComponent *camera)
    {
        auto transComp = entity->GetComponent<TransformComponent>();
        auto spriteComp = entity->GetComponent<RenderComponent>();

        mGizmoMaterial->GetShaderProgram()->SetActive(true);

        mGizmoMaterial->GetShaderProgram()->SetUniformValue("modelMat", transComp->GetModelMat());
        mGizmoMaterial->GetShaderProgram()->SetUniformValue("viewMat", camera->GetViewMat());
        mGizmoMaterial->GetShaderProgram()->SetUniformValue("projMat", camera->GetProjMat());

        mGizmoMaterial->SetUniformValue();

        mGizmoMaterial->GetShaderProgram()->SetVertexArray(mPointPrimitive->GetVertexArray());

        mGizmoMaterial->GetShaderProgram()->SetVertexBuffer("inPosition", mPointPrimitive->GetPositionBuffer());

        mRasterPipeline->SetPointSize(5);
        mRasterPipeline->Render(*mPointPrimitive, PrimitiveRenderType::POINT_LIST);
        mRasterPipeline->SetPointSize(1);

        mGizmoMaterial->GetShaderProgram()->ResetVertexBuffer("inPosition");

        mGizmoMaterial->ResetUniformValue();

        mGizmoMaterial->GetShaderProgram()->ResetVertexArray();

        mGizmoMaterial->GetShaderProgram()->SetActive(false);
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

        mGizmoMaterial->SetUniformValue();

        mGizmoMaterial->GetShaderProgram()->SetVertexArray(mQuadPrimitive->GetVertexArray());

        mGizmoMaterial->GetShaderProgram()->SetVertexBuffer("inPosition", mQuadPrimitive->GetPositionBuffer());

        mRasterPipeline->Render(*mQuadPrimitive, PrimitiveRenderType::LINE_LIST);

        mGizmoMaterial->GetShaderProgram()->ResetVertexBuffer("inPosition");

        mGizmoMaterial->ResetUniformValue();

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

        mGizmoMaterial->SetUniformValue();

        mGizmoMaterial->GetShaderProgram()->SetVertexArray(mCirclePrimitive->GetVertexArray());

        mGizmoMaterial->GetShaderProgram()->SetVertexBuffer("inPosition", mCirclePrimitive->GetPositionBuffer());

        mRasterPipeline->Render(*mCirclePrimitive, PrimitiveRenderType::LINE_LIST);

        mGizmoMaterial->GetShaderProgram()->ResetVertexBuffer("inPosition");

        mGizmoMaterial->ResetUniformValue();

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
            mRasterPipeline->SetViewport(App::GetInstance().GetWindow()->GetViewport());

            mRasterPipeline->SetBufferClearColor(camera->GetClearColor());

            mRasterPipeline->ClearColorBuffer();

            mRasterPipeline->SetCull(CullType::BACK);

            mRasterPipeline->SetDepthTest(DepthTestType::NONE);

            mRasterPipeline->SetBlendState(true,BlendFunc::SRC_ALPHA,BlendFunc::ONE_MINUS_SRC_ALPHA);

            // render sprite
            for (const auto &entity : entitiesWithSpriteComp)
                RenderSprite(entity, camera);
        }
    }
}