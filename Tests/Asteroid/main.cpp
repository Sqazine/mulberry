#include "libmulberry/libmulberry.h"
#include "ShipMoveComponent.h"
#undef main
int main(int argc, char **argv)
{
    mulberry::WindowInfo winInfo{};
    winInfo.title = "Asteroid";
    winInfo.width = 1024;
    winInfo.height = 768;

    mulberry::GL::RenderContextInfo info{};
    info.windowInfo = winInfo;
    mulberry::App::Init(info);

    mulberry::Scene *scene = mulberry::App::CreateScene("Asteroid");
 

    mulberry::Entity *rootEntity = scene->CreateEntity("Ship");
    if (rootEntity)
    {
        mulberry::SpriteComponent *spriteComponent = rootEntity->CreateComponent<mulberry::SpriteComponent>();
    }

    rootEntity->CreateComponent<ShipMoveComponent>();

    mulberry::Entity *cameraEntity = scene->CreateEntity("Camera");
    auto cameraComp = cameraEntity->CreateComponent<mulberry::CameraComponent>();
    if (cameraComp)
    {
        cameraComp->SetClearColor(mulberry::Color::LightYellow);
        cameraComp->SetExtent(mulberry::Vec2(winInfo.width, winInfo.height));
    }

    mulberry::App::Run();

    return 0;
}