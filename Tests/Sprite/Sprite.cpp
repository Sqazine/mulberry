#include "libPe2/libPe2.h"
int main(int argc,char** argv)
{
    Pe2::Scene* scene=Pe2::App::CreateScene("Sprite");

    Pe2::Entity* rootEntity=scene->CreateEntity("Sprite");
    Pe2::Entity* spriteEntity=scene->CreateEntity("Sprite");
    Pe2::Component* cameraComp= rootEntity->CreateComponent<Pe2::CameraComponent>();

    Pe2::App::Run();

    return 0;
}