#include "mulberry/mulberry.h"

class AppQuitComponent : public mulberry::Component
{
public:
    AppQuitComponent() = default;
    ~AppQuitComponent() = default;

    void Update() override
    {
        if (mulberry::App::GetInstance().GetWindow()->IsWindowCloseButtonClick())
            mulberry::App::GetInstance().Quit();
    }
};

OGL_USE_DISCRETE_CARD
int32_t main(int32_t argc, char **argv)
{
    mulberry::App::GetInstance().SetGraphicsBackend(mulberry::GraphicsBackend::VK);
    mulberry::App::GetInstance().Init();

    mulberry::App::GetInstance().GetWindow()->SetTitle("Sprite");
    mulberry::App::GetInstance().GetWindow()->Resize(1024, 768);

    mulberry::Scene *scene = mulberry::App::GetInstance().CreateScene("Sprite");
    mulberry::TextureInfo textureInfo{};
    textureInfo.data = scene->GetSceneAssetManager()->LoadImgData("Assets/awesomeface.png");

    auto texture = std::make_unique<mulberry::Texture>(textureInfo);

    mulberry::Entity *rootEntity = scene->CreateEntity("Sprite");

    auto cameraComp = rootEntity->CreateComponent<mulberry::CameraComponent>();
    if (cameraComp)
    {
        cameraComp->SetClearColor(mulberry::Color::LightYellow);
        cameraComp->SetExtent(mulberry::App::GetInstance().GetWindow()->GetSize());
    }

    mulberry::SpriteComponent *spriteComponent = rootEntity->CreateComponent<mulberry::SpriteComponent>();
    spriteComponent->SetSprite(texture.get());

    rootEntity->CreateComponent<AppQuitComponent>();

    mulberry::App::GetInstance().Run();

    return 0;
}