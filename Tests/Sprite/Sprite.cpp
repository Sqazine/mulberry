#include "libPe2/libPe2.h"
int32_t main(int32_t argc,char** argv)
{

    Pe2::WindowInfo winInfo{};
    winInfo.title="Sprite";
    winInfo.width=1024;
    winInfo.height=768;

    Pe2::RenderContextInfo info{};
    info.windowInfo=winInfo;
    Pe2::App::Init(info);


    Pe2::Scene* scene=Pe2::App::CreateScene("Sprite");
    Pe2::TextureInfo textureInfo{};
    textureInfo.data=scene->GetResourceManager().LoadImgData(std::string(RESOURCES_DIR)+"awesomeface.png");

    Pe2::Entity* rootEntity=scene->CreateEntity("Sprite");

    auto cameraComp= rootEntity->CreateComponent<Pe2::CameraComponent>();
    cameraComp->SetClearColor(Pe2::Color::LightYellow);
    cameraComp->SetExtent(Pe2::Vec2(winInfo.width,winInfo.height));

    Pe2::SpriteComponent* spriteComponent=rootEntity->CreateComponent<Pe2::SpriteComponent>();
    spriteComponent->SetTexture(new Pe2::Texture(textureInfo));


    Pe2::App::Run();

    return 0;
}