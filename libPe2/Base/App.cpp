#include "App.h"
#include "Render/Renderer.h"
#include "Render/GL/RenderContext.h"
#include "Input.h"
namespace Pe2
{
    AppState App::mState = AppState::INIT;

    Timer App::mTimer;
    Input App::mInput;

    std::vector<std::unique_ptr<Scene>> App::mScenes;
    int32_t App::mSceneIdx = 0;

    SceneRenderer App::mSceneRenderer;

    void App::Run()
    {
        while (mState != AppState::EXIT)
        {
            mTimer.Update();
            ProcessInput();
            Update();
            Render();
            RenderGizmo();
            RenderUI();
            GL::RenderContext::SwapWindow();
        }
        CleanUp();
    }

    Scene *App::CreateScene(std::string_view name)
    {
        auto scene = std::make_unique<Scene>(name);
        Scene *result = scene.get();
        mScenes.emplace_back(std::move(scene));
        return result;
    }

    Scene *App::GetScene(std::string_view name)
    {
        auto iter = std::find_if(mScenes.begin(), mScenes.end(), [=](auto &scene)
                                 { return scene->GetName() == name; });
        if (iter == mScenes.end())
            return nullptr;
        return iter->get();
    }

    bool App::RemoveScene(std::string_view name)
    {
        auto iter = std::find_if(mScenes.begin(), mScenes.end(), [=](auto &scene)
                                 { return scene->GetName() == name; });
        bool exists = iter != mScenes.end();
        if (exists)
            mScenes.erase(iter);
        return exists;
    }

    void App::RemoveAllScenes()
    {
        std::vector<std::unique_ptr<Scene>>().swap(mScenes);
    }

    void App::Quit()
    {
        mState = AppState::EXIT;
    }

    void App::Init(const GL::RenderContextInfo &info)
    {
        GL::RenderContext::Init(info);
        mInput.Init();

        mSceneIdx = 0;
        mSceneRenderer.Init();

        mTimer.Init();
    }

    void App::ProcessInput()
    {
        SDL_Event event;
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                mState = AppState::EXIT;
            }
        }

        mInput.ProcessInput(event);

        for (const auto &entity : mScenes[mSceneIdx]->GetAllEntities())
            for (const auto &comp : entity->GetAllComponents())
                comp->ProcessInput(mInput.GetDevice());
    }
    void App::Update()
    {
        mInput.PreUpdate();

        for (const auto &entity : mScenes[mSceneIdx]->GetAllEntities())
        {
            for (const auto &comp : entity->GetAllComponents())
            {
                comp->Update(mTimer.GetDeltaTime());
                comp->LateUpdate(mTimer.GetDeltaTime());
            }
        }

        mInput.PostUpdate();
    }
    void App::Render()
    {
        mSceneRenderer.Render(mScenes[mSceneIdx].get());
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
        SDL_SetWindowSize(GL::RenderContext::GetWindow(), extent.x, extent.y);
    }
    Vec2 App::GetWindowExtent()
    {
        int32_t x, y;
        SDL_GetWindowSize(GL::RenderContext::GetWindow(), &x, &y);
        return Vec2(x, y);
    }
}