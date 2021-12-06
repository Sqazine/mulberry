#include "App.h"
namespace Pe2
{
    AppState App::m_State = AppState::INIT;

    std::vector<std::unique_ptr<Scene>> App::m_Scenes;

    void App::Run()
    {
        Init();
        while (m_State != AppState::EXIT)
        {
            ProcessInput();
            Update();
            Draw();
        }
        CleanUp();
    }

    Scene *App::CreateScene(std::string_view name)
    {
        auto scene = std::make_unique<Scene>(name);
        Scene *result = scene.get();
        m_Scenes.emplace_back(std::move(scene));
        return result;
    }

    void App::RemoveScene(std::string_view name)
    {
        
    }

    void App::Init()
    {
    }
    void App::ProcessInput()
    {
    }
    void App::Update()
    {
    }
    void App::Draw()
    {
    }
    void App::CleanUp()
    {
    }
}