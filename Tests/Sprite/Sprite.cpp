#include "libmulberry/libmulberry.h"
int32_t main(int32_t argc, char **argv)
{

    mulberry::WindowInfo winInfo{};
    winInfo.title = "Sprite";
    winInfo.width = 1024;
    winInfo.height = 768;

    mulberry::GL::RenderContextInfo info{};
    info.windowInfo = winInfo;
    mulberry::App::Init(info);

    mulberry::Scene *scene = mulberry::App::CreateScene("Sprite");
    mulberry::GL::TextureInfo textureInfo{};
    textureInfo.data = scene->GetSceneAssetManager()->LoadImgData(std::string(RESOURCES_DIR) + "awesomeface.png");

    auto texture=std::make_unique<mulberry::GL::Texture>(textureInfo);

    mulberry::Entity *rootEntity = scene->CreateEntity("Sprite");

    auto cameraComp = rootEntity->CreateComponent<mulberry::CameraComponent>();
    if (cameraComp)
    {
        cameraComp->SetClearColor(mulberry::Color::LightYellow);
        cameraComp->SetExtent(mulberry::Vec2(winInfo.width, winInfo.height));
    }

    mulberry::SpriteComponent *spriteComponent = rootEntity->CreateComponent<mulberry::SpriteComponent>();
    spriteComponent->SetSprite(texture.get());;

    mulberry::App::Run();

    return 0;
}