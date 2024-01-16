#include "SceneRenderer.h"
#include "Pipeline.h"
#include "App.h"
#include "Material.h"
namespace mulberry
{
    void SceneRenderer::Init()
    {
        mGizmoMaterial = std::make_unique<GizmoMaterial>();

        mQuadPrimitive = std::make_unique<PrimitiveGeometry>(PrimitiveGeometryType::QUAD);
        mSpritePrimitive = std::make_unique<PrimitiveGeometry>(PrimitiveGeometryType::SPRITE);
        mLinePrimitive = std::make_unique<PrimitiveGeometry>(PrimitiveGeometryType::LINE);
        mCirclePrimitive = std::make_unique<PrimitiveGeometry>(PrimitiveGeometryType::CIRCLE);

		/*  mSpriteRasterPipeline = std::make_unique<RasterPipeline>();
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
		  mPointRasterPipeline->GetPSO().pointSize = 5;*/
    }

    void SceneRenderer::RenderSprite(const Entity *entity, CameraComponent *camera)
    {
        auto transComp = entity->GetComponent<TransformComponent>();
        auto spriteComp = entity->GetComponent<SpriteComponent>();
        const SpriteMaterial *material = (SpriteMaterial *)spriteComp->GetMaterial();

        // map to sprite size
        Mat4 mat = transComp->GetModelMat();
      //  mat *= Mat4::Scale(Vec2(material->GetSprite()->GetCreateInfo().data.width / 2, material->GetSprite()->GetCreateInfo().data.height / 2));

      /*  material->GetShaderGroup()->SetActive(true);
        material->GetShaderGroup()->SetDefaultUniformValue("modelMat", mat);
        material->GetShaderGroup()->SetDefaultUniformValue("viewMat", camera->GetViewMat());
        material->GetShaderGroup()->SetDefaultUniformValue("projMat", camera->GetProjMat());

        material->SetDefaultUniformValue();

        material->GetShaderGroup()->SetVertexArray(mSpritePrimitive->GetVertexArray());

        material->GetShaderGroup()->SetVertexBuffer("inPosition", mSpritePrimitive->GetPositionBuffer());
        material->GetShaderGroup()->SetVertexBuffer("inTexcoord", mSpritePrimitive->GetTexcoordBuffer());

        mSpriteRasterPipeline->Render(*mSpritePrimitive);

        material->GetShaderGroup()->ResetVertexBuffer("inTexcoord");
        material->GetShaderGroup()->ResetVertexBuffer("inPosition");

        material->GetShaderGroup()->ResetVertexArray();

        material->ResetUniformValue();

        material->GetShaderGroup()->SetActive(false);*/
    }

    void SceneRenderer::RenderAuxiliary(const Entity *entity, CameraComponent *camera, const PrimitiveGeometry &primitive)
    {
        auto transComp = entity->GetComponent<TransformComponent>();
        auto spriteComp = entity->GetComponent<RenderComponent>();

        const SpriteMaterial *material = (SpriteMaterial *)spriteComp->GetMaterial();

        // map to sprite size
       /* Mat4 mat = transComp->GetModelMat();
        mat *= Mat4::Scale(Vec2(material->GetSprite()->GetCreateInfo().data.width / 2, material->GetSprite()->GetCreateInfo().data.height / 2));

        mGizmoMaterial->GetShaderGroup()->SetActive(true);

        mGizmoMaterial->GetShaderGroup()->SetDefaultUniformValue("modelMat", mat);
        mGizmoMaterial->GetShaderGroup()->SetDefaultUniformValue("viewMat", camera->GetViewMat());
        mGizmoMaterial->GetShaderGroup()->SetDefaultUniformValue("projMat", camera->GetProjMat());

        mGizmoMaterial->SetDefaultUniformValue();

        mGizmoMaterial->GetShaderGroup()->SetVertexArray(primitive.GetVertexArray());

        mGizmoMaterial->GetShaderGroup()->SetVertexBuffer("inPosition", primitive.GetPositionBuffer());

        mAuxiliaryRasterPipeline->Render(primitive);
        mPointRasterPipeline->Render(primitive);

        mGizmoMaterial->GetShaderGroup()->ResetVertexBuffer("inPosition");

        mGizmoMaterial->ResetUniformValue();

        mGizmoMaterial->GetShaderGroup()->ResetVertexArray();

        mGizmoMaterial->GetShaderGroup()->SetActive(false);*/
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
           // mSpriteRasterPipeline->GetPSO().viewport = App::GetInstance().GetWindow()->GetViewport();

            App::GetInstance().GetGraphicsContext()->SetClearColor(camera->GetClearColor());
            App::GetInstance().GetGraphicsContext()->IsClearColorBuffer(true);

            App::GetInstance().GetGraphicsContext()->BeginFrame();

            // render sprite
            for (const auto &entity : entitiesWithSpriteComp)
            {
                RenderSprite(entity, camera);
                RenderAuxiliary(entity, camera, *mLinePrimitive);
                RenderAuxiliary(entity, camera, *mCirclePrimitive);
                RenderAuxiliary(entity, camera, *mQuadPrimitive);
            }

            App::GetInstance().GetGraphicsContext()->EndFrame();
        }
    }
}