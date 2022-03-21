#include "libPe2/libPe2.h"
#include "ShipMoveComponent.h"
#undef main
int main(int argc, char **argv)
{
    Pe2::WindowInfo winInfo{};
    winInfo.title = "Asteroid";
    winInfo.width = 1024;
    winInfo.height = 768;

    Pe2::GL::RenderContextInfo info{};
    info.windowInfo = winInfo;
    Pe2::App::Init(info);

    Pe2::Scene *scene = Pe2::App::CreateScene("Asteroid");
 

    Pe2::Entity *rootEntity = scene->CreateEntity("Ship");
    if (rootEntity)
    {
        Pe2::SpriteComponent *spriteComponent = rootEntity->CreateComponent<Pe2::SpriteComponent>();
    }

    rootEntity->CreateComponent<ShipMoveComponent>();

    Pe2::Entity *cameraEntity = scene->CreateEntity("Camera");
    auto cameraComp = cameraEntity->CreateComponent<Pe2::CameraComponent>();
    if (cameraComp)
    {
        cameraComp->SetClearColor(Pe2::Color::LightYellow);
        cameraComp->SetExtent(Pe2::Vec2(winInfo.width, winInfo.height));
    }

    Pe2::App::Run();

    return 0;
}