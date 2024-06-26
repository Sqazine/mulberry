#include "App.h"
#include "Logger.h"
#include "SceneRenderer.h"
#include "GraphicsContext.h"
#include "AppConfig.h"

#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
#include "Platform/SDL2/InputImpl.h"
#include "Platform/SDL2/TimerImpl.h"
#include "Platform/SDL2/WindowImpl.h"
#else
#endif

namespace mulberry
{
	void App::Run()
	{
		mWindow->Show();
		while (mState != AppState::EXIT)
		{
			PreUpdate();
			Update();
			Render();
			RenderGizmo();
			PostUpdate();
		}
		Destroy();
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

	void App::SetGraphicsBackend(GraphicsBackend graphicsBackend)
	{
		AppConfig::graphicsConfig.backend = graphicsBackend;
	}

	GraphicsConfig &App::GetGraphicsConfig()
	{
		return AppConfig::graphicsConfig;
	}

	Window *App::GetWindow() const
	{
		return mWindow.get();
	}

	Input *App::GetInput() const
	{
		return mInput.get();
	}

	Timer *App::GetTimer() const
	{
		return mTimer.get();
	}

	GraphicsContext *App::GetGraphicsContext() const
	{
		return mGraphicsContext.get();
	}

	void App::Init()
	{
#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
		mInput = std::make_unique<SDL2InputImpl>();
		mTimer = std::make_unique<SDL2TimerImpl>();
		mWindow = std::make_unique<SDL2WindowImpl>();
#else
#error "Not Support Platform,only windows is available now!"
#endif
		Logger::GetInstance().Init();
		mInput->Init();
		mTimer->Init();

		mGraphicsContext = std::make_unique<GraphicsContext>();
		mGraphicsContext->Init();

		mSceneIdx = 0;
		mSceneRenderer = std::make_unique<SceneRenderer>();
	}

	void App::Update()
	{
		if (AppConfig::refreshOnlyWindowIsActive && GetWindow()->HasEvent(Window::Event::MIN))
			mState = AppState::PAUSE;
		else if (GetWindow()->HasEvent(Window::Event::ENTER | Window::Event::EXPOSE))
			mState = AppState::UPDATE;

		if (!AppConfig::graphicsConfig.useVSync)
			mTimer->Update(AppConfig::graphicsConfig.frameRate);
		else
			mTimer->Update();

		if (mState != AppState::PAUSE)
		{
			for (const auto &entity : mScenes[mSceneIdx]->GetAllEntities())
			{
				for (const auto &comp : entity->GetAllComponents())
				{
					comp->Update();
					comp->LateUpdate();
				}
			}
		}
	}

	void App::Render()
	{
		if (mState != AppState::PAUSE)
			mSceneRenderer->Render(mScenes[mSceneIdx].get());
	}

	void App::RenderGizmo()
	{
	}

	void App::Destroy()
	{
		for (auto &scene : mScenes)
			scene.reset(nullptr);

		mSceneRenderer.reset(nullptr);
	}

	void App::PreUpdate()
	{
		mInput->PreUpdate();
	}

	void App::PostUpdate()
	{
		if (mWindow->HasEvent(Window::Event::CLOSE))
			Quit();

		mWindow->ClearEvent();
		mInput->PostUpdate();
	}
}