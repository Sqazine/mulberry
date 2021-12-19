#include "libPe2/libPe2.h"
#include "ShipMoveComponent.h"
#undef main
int main(int argc, char **argv)
{
    Pe2::WindowInfo winInfo{};
    winInfo.title = "Asteroid";
    winInfo.width = 1024;
    winInfo.height = 768;

    Pe2::RenderContextInfo info{};
    info.windowInfo = winInfo;
    Pe2::App::Init(info);

    Pe2::Scene *scene = Pe2::App::CreateScene("Asteroid");
    Pe2::TextureInfo textureInfo{};
    textureInfo.data = scene->GetResourceManager().LoadImgData(std::string(RESOURCES_DIR) + "Ship.png");
    textureInfo.filterMode=Pe2::FilterMode::LINEAR;

    Pe2::Entity *rootEntity = scene->CreateEntity("Ship");
    Pe2::SpriteComponent *spriteComponent = rootEntity->CreateComponent<Pe2::SpriteComponent>();
    spriteComponent->SetTexture(new Pe2::Texture(textureInfo));

    auto transComponent= rootEntity->GetComponent<Pe2::TransformComponent>();
    transComponent->SetRotation(90.0f);
    transComponent->SetPosition(0.0f,(-Pe2::App::GetWindowExtent().y+textureInfo.data.height*transComponent->GetScale().y)/2.0f);

    rootEntity->CreateComponent<ShipMoveComponent>();

    Pe2::Entity* cameraEntity=scene->CreateEntity("Camera");
    auto cameraComp = cameraEntity->CreateComponent<Pe2::CameraComponent>();
    cameraComp->SetClearColor(Pe2::Color::LightYellow);
    cameraComp->SetExtent(Pe2::Vec2(winInfo.width, winInfo.height));

    Pe2::App::Run();

    return 0;
}