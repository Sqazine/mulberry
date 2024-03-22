#include "SceneRenderer.h"
#include "Pipeline.h"
#include "App.h"
#include "Material.h"
#include "Graphics/RHI/Pass.h"
#include "Graphics/RHI/Enum.h"
namespace mulberry
{
    SceneRenderer::SceneRenderer()
    {
        mGizmoMaterial = std::make_unique<GizmoMaterial>();

        mQuadPrimitive = std::make_unique<PrimitiveGeometry>(PrimitiveGeometryType::QUAD);
        mSpritePrimitive = std::make_unique<PrimitiveGeometry>(PrimitiveGeometryType::SPRITE);
        mLinePrimitive = std::make_unique<PrimitiveGeometry>(PrimitiveGeometryType::LINE);
        mCirclePrimitive = std::make_unique<PrimitiveGeometry>(PrimitiveGeometryType::CIRCLE);
    }

    SceneRenderer::~SceneRenderer()
    {
    }

    void SceneRenderer::RenderSprite(rhi::SwapChainPass *pass, const Entity *entity, CameraComponent *camera)
    {
        auto transComp = entity->GetComponent<TransformComponent>();
        auto spriteComp = entity->GetComponent<SpriteComponent>();
        const SpriteMaterial *material = (SpriteMaterial *)spriteComp->GetMaterial();

        // map to sprite size
        Mat4 mat = transComp->GetModelMat();
        //  mat *= Mat4::Scale(Vec2(material->GetSprite()->GetCreateInfo().data.width / 2, material->GetSprite()->GetCreateInfo().data.height / 2));

        // pass->SetPipeline(*spriteComp->GetMaterial()->GetGraphicsPipeline());

        /*  material->GetShaderGroup()->SetActive(true);
          material->GetShaderGroup()->SetDefaultUniformValue("modelMat", mat);
          material->GetShaderGroup()->SetDefaultUniformValue("viewMat", camera->GetViewMat());
          material->GetShaderGroup()->SetDefaultUniformValue("projMat", camera->GetProjMat());

          material->SetDefaultUniformValue();

          material->GetShaderGroup()->SetVertexArray(mSpritePrimitive->GetVertexArray());

          material->GetShaderGroup()->SetVertexBuffer("inPosition", mSpritePrimitive->GetPositionBuffer());
          material->GetShaderGroup()->SetVertexBuffer("inTexcoord", mSpritePrimitive->GetTexcoordBuffer());

          mSpriteGraphicsPipeline->Render(*mSpritePrimitive);

          material->GetShaderGroup()->ResetVertexBuffer("inTexcoord");
          material->GetShaderGroup()->ResetVertexBuffer("inPosition");

          material->GetShaderGroup()->ResetVertexArray();

          material->ResetUniformValue();

          material->GetShaderGroup()->SetActive(false);*/
    }

    void SceneRenderer::RenderAuxiliary(rhi::SwapChainPass *pass, const Entity *entity, CameraComponent *camera, const PrimitiveGeometry &primitive)
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

         mAuxiliaryGraphicsPipeline->Render(primitive);
         mPointGraphicsPipeline->Render(primitive);

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
            auto swapChainPass = App::GetInstance().GetGraphicsContext()->GetSwapChainPass();

            swapChainPass->SetClearColor(camera->GetClearColor());
            swapChainPass->IsClearColorBuffer(true);

            swapChainPass->Begin();

            swapChainPass->SetViewport(camera->GetViewport());

            for (const auto &entity : entitiesWithSpriteComp)
            {
                RenderSprite(swapChainPass, entity, camera);
                RenderAuxiliary(swapChainPass, entity, camera, *mLinePrimitive);
                RenderAuxiliary(swapChainPass, entity, camera, *mCirclePrimitive);
                RenderAuxiliary(swapChainPass, entity, camera, *mQuadPrimitive);
            }

            swapChainPass->End();
        }
    }
}