#include "libmulberry/libmulberry.h"
#include "ShipMoveComponent.h"
#undef main
int main(int argc, char **argv)
{

     mulberry::App::GetInstance().SetGraphicsBackend(mulberry::GraphicsBackend::GL);
    mulberry::App::GetInstance().Init();

    mulberry::App::GetInstance().GetWindow()->SetTitle("Asteroid");
    mulberry::App::GetInstance().GetWindow()->Resize(1024,768);

    mulberry::Scene *scene = mulberry::App::GetInstance().CreateScene("Asteroid");
 

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
        cameraComp->SetExtent(mulberry::App::GetInstance().GetWindow()->GetSize());
    }

    mulberry::App::GetInstance().Run();

    return 0;
}