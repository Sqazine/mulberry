#include "libPe2/libPe2.h"
int32_t main(int32_t argc,char** argv)
{
    Pe2::Scene* scene=Pe2::App::CreateScene("Sprite");

    Pe2::Entity* rootEntity=scene->CreateEntity("Sprite");
    Pe2::Entity* spriteEntity=scene->CreateEntity("Sprite");
    Pe2::Component* cameraComp= rootEntity->CreateComponent<Pe2::CameraComponent>();

    Pe2::WindowInfo winInfo{};
    winInfo.title="Sprite";
    winInfo.width=1024;
    winInfo.height=768;
    winInfo.flags=Pe2::WINDOW_BORDERLESS;

    Pe2::RenderContextInfo info{};
    info.windowInfo=winInfo;

    Pe2::App::Init(info);
    Pe2::App::Run();

    return 0;
}