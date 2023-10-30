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
        mCirclePrimitive = std::make_unique<Primitive>(PrimitiveType::CIRCLE);

        mDrawPass = std::make_unique<DrawPass>();

        mSpriteRasterPipeline = std::make_unique<RasterPipeline>();
        mSpriteRasterPipeline->GetPSO().cullType = CullType::BACK;
        mSpriteRasterPipeline->GetPSO().depthTest = DepthTest::NONE;
        mSpriteRasterPipeline->GetPSO().blendState = {true, BlendFunc::SRC_ALPHA, BlendFunc::ONE_MINUS_SRC_ALPHA};
        mSpriteRasterPipeline->GetPSO().primitiveRenderType = PrimitiveRenderType::TRIANGLE_LIST;

        mAuxiliaryRasterPipeline = std::make_unique<RasterPipeline>();
        mAuxiliaryRasterPipeline->GetPSO().cullType = CullType::BACK;
        mAuxiliaryRasterPipeline->GetPSO().depthTest = DepthTest::NONE;
        mAuxiliaryRasterPipeline->GetPSO().blendState = {true, BlendFunc::SRC_ALPHA, BlendFunc::ONE_MINUS_SRC_ALPHA};
        mAuxiliaryRasterPipeline->GetPSO().primitiveRenderType = PrimitiveRenderType::LINE_LIST;

        mPointRasterPipeline = std::make_unique<RasterPipeline>();
        mPointRasterPipeline->GetPSO().cullType = CullType::BACK;
        mPointRasterPipeline->GetPSO().depthTest = DepthTest::NONE;
        mPointRasterPipeline->GetPSO().blendState = {true, BlendFunc::SRC_ALPHA, BlendFunc::ONE_MINUS_SRC_ALPHA};
        mPointRasterPipeline->GetPSO().primitiveRenderType = PrimitiveRenderType::POINT_LIST;
        mPointRasterPipeline->GetPSO().pointSize = 5;
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

        mSpriteRasterPipeline->Render(*mSpritePrimitive);

        material->GetShaderProgram()->ResetVertexBuffer("inTexcoord");
        material->GetShaderProgram()->ResetVertexBuffer("inPosition");

        material->GetShaderProgram()->ResetVertexArray();

        material->ResetUniformValue();

        material->GetShaderProgram()->SetActive(false);
    }

    void SceneRenderer::RenderAuxiliary(const Entity *entity, CameraComponent *camera, const Primitive &primitive)
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

        mGizmoMaterial->GetShaderProgram()->SetVertexArray(primitive.GetVertexArray());

        mGizmoMaterial->GetShaderProgram()->SetVertexBuffer("inPosition", primitive.GetPositionBuffer());

        mAuxiliaryRasterPipeline->Render(primitive);
        mPointRasterPipeline->Render(primitive);

        mGizmoMaterial->GetShaderProgram()->ResetVertexBuffer("inPosition");

        mGizmoMaterial->ResetUniformValue();

        mGizmoMaterial->GetShaderProgram()->ResetVertexArray();

        mGizmoMaterial->GetShaderProgram()->SetActive(false);
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
            mSpriteRasterPipeline->GetPSO().viewport = App::GetInstance().GetWindow()->GetViewport();

            mDrawPass->SetClearColor(camera->GetClearColor());
            mDrawPass->IsClearColorBuffer(true);

            mDrawPass->Begin();

            // render sprite
            for (const auto &entity : entitiesWithSpriteComp)
            {
                RenderSprite(entity, camera);
                RenderAuxiliary(entity, camera, *mLinePrimitive);
                RenderAuxiliary(entity, camera, *mCirclePrimitive);
                RenderAuxiliary(entity, camera, *mQuadPrimitive);
            }

            mDrawPass->End();
        }
    }
}