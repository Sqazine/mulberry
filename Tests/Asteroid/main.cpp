#include "libmulberry.h"
#include "ShipMoveComponent.h"
#include "ShipShootComponent.h"

int main(int argc, char **argv)
{

    mulberry::App::GetInstance().SetGraphicsBackend(mulberry::GraphicsBackend::VK);
    mulberry::App::GetInstance().Init();

    mulberry::App::GetInstance().GetWindow()->SetTitle("Asteroid");
    mulberry::App::GetInstance().GetWindow()->Resize(1024, 768);

    mulberry::Scene *scene = mulberry::App::GetInstance().CreateScene("Asteroid");

    mulberry::Entity *rootEntity = scene->CreateEntity("Ship");
    if (rootEntity)
    {
        mulberry::SpriteComponent *spriteComponent = rootEntity->CreateComponent<mulberry::SpriteComponent>();
    }

    rootEntity->CreateComponent<ShipMoveComponent>();
    rootEntity->CreateComponent<ShipShootComponent>();

    mulberry::Entity *cameraEntity = scene->CreateEntity("Camera");
    auto cameraComp = cameraEntity->CreateComponent<mulberry::CameraComponent>();
    if (cameraComp)
    {
        cameraComp->SetClearColor(mulberry::Color::LightYellow);
        cameraComp->SetViewport(mulberry::App::GetInstance().GetWindow()->GetViewport());
    }

    mulberry::App::GetInstance().Run();

    return 0;
}