#include "App.h"
#include "Render/Renderer.h"
#include "Render/RenderContext.h"
#include "Input/Input.h"
namespace Pe2
{
    AppState App::m_State = AppState::INIT;

    Timer App::m_Timer;
    Input App::m_Input;

    std::vector<std::unique_ptr<Scene>> App::m_Scenes;
    int32_t App::m_SceneIdx = 0;

    SceneRenderer App::m_SceneRenderer;

    void App::Run()
    {
        while (m_State != AppState::EXIT)
        {
            m_Timer.Update();
            ProcessInput();
            Update();
            Render();
            RenderGizmo();
            RenderUI();
            RenderContext::SwapWindow();
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

    Scene *App::GetScene(std::string_view name)
    {
        auto iter = std::find_if(m_Scenes.begin(), m_Scenes.end(), [=](auto &scene)
                                 { return scene->GetName() == name; });
        if (iter == m_Scenes.end())
            return nullptr;
        return iter->get();
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
        std::vector<std::unique_ptr<Scene>>().swap(m_Scenes);
    }

    void App::Quit()
    {
        m_State = AppState::EXIT;
    }

    void App::Init(const RenderContextInfo &info)
    {
        RenderContext::Init(info);
        m_Input.Init();

        m_SceneIdx = 0;
        m_SceneRenderer.Init();

        m_Timer.Init();
    }

    void App::ProcessInput()
    {
        SDL_Event event;
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                m_State = AppState::EXIT;
            }
        }

        m_Input.ProcessInput(event);

        for (const auto &entity : m_Scenes[m_SceneIdx]->GetAllEntities())
            for (const auto &comp : entity->GetAllComponents())
                comp->ProcessInput(m_Input.GetDevice());
    }
    void App::Update()
    {
        m_Input.PreUpdate();

        for (const auto &entity : m_Scenes[m_SceneIdx]->GetAllEntities())
        {
            for (const auto &comp : entity->GetAllComponents())
            {
                comp->Update(m_Timer.GetDeltaTime());
                comp->LateUpdate(m_Timer.GetDeltaTime());
            }
        }

        m_Input.PostUpdate();
    }
    void App::Render()
    {
        m_SceneRenderer.Render(m_Scenes[m_SceneIdx].get());
    }

    void App::RenderGizmo()
    {
    }

    void App::RenderUI()
    {
    }

    void App::CleanUp()
    {
    }

    void App::SetWindowExtent(const Vec2 &extent)
    {
        SDL_SetWindowSize(RenderContext::GetWindow(), extent.x, extent.y);
    }
    Vec2 App::GetWindowExtent()
    {
        int32_t x, y;
        SDL_GetWindowSize(RenderContext::GetWindow(), &x, &y);
        return Vec2(x, y);
    }
}