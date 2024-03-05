#include "mulberry.h"

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

int32_t main(int32_t argc, char **argv)
{
    mulberry::App::GetInstance().SetGraphicsBackend(mulberry::GraphicsBackend::VK);
    mulberry::App::GetInstance().Init();

    mulberry::App::GetInstance().GetWindow()->SetTitle("Sprite");
    mulberry::App::GetInstance().GetWindow()->Resize(1024, 768);

    mulberry::Scene *scene = mulberry::App::GetInstance().CreateScene("Sprite");

    auto imgData = scene->GetSceneAssetManager()->LoadImageData("Assets/awesomeface.png");

    auto texture = std::make_unique<mulberry::rhi::Texture>();
    texture->SetImageData(imgData)
        .SetMagFilter(mulberry::rhi::FilterMode::LINEAR)
        .SetMinFilter(mulberry::rhi::FilterMode::LINEAR)
        .SetBorderColor(mulberry::rhi::BorderColor::FLOAT_TRANSPARENT_BLACK);

    mulberry::Entity *rootEntity = scene->CreateEntity("Sprite");

    rootEntity->CreateComponent<AppQuitComponent>();

	auto cameraComp = rootEntity->CreateComponent<mulberry::CameraComponent>();
	if (cameraComp)
	{
		cameraComp->SetClearColor(mulberry::Color::LightYellow);
		cameraComp->SetViewport(mulberry::App::GetInstance().GetWindow()->GetViewport());
	}

	mulberry::SpriteComponent* spriteComponent = rootEntity->CreateComponent<mulberry::SpriteComponent>();
	spriteComponent->SetSprite(texture.get());

    mulberry::App::GetInstance().Run();

    return 0;
}