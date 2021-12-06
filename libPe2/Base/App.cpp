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

    bool App::RemoveScene(std::string_view name)
    {
        auto iter = std::find_if(m_Scenes.begin(), m_Scenes.end(), [=](auto &scene)
                                 { return scene->GetName() == name; });
        bool exists = iter != m_Scenes.end();
        if (exists)
            m_Scenes.erase(iter);
        return exists;
    }

    void App::RemoveAllScenes()
    {
    }

    void App::Quit()
    {
        m_State = AppState::EXIT;
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