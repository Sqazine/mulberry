#include "App.h"
#include "SceneRenderer.h"
#include "GraphicsContext.h"
#include "Logger.h"
#include "AppGlobalConfig.h"

#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
#include "Platform/SDL2/GLContextImpl.h"
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
			mTimer->Update();
			Update();
			GraphicsContext::GetInstance().BeginFrame();
			Render();
			GraphicsContext::GetInstance().EndFrame();
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

	void App::SetGraphicsBackend(GraphicsBackend graphicsBackend)
	{
		AppGlobalConfig::gGraphicsConfig.backend = graphicsBackend;
	}

	const GraphicsConfig &App::GetGraphicsConfig() const
	{
		return AppGlobalConfig::gGraphicsConfig;
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

	void App::Init()
	{

#if defined(PLATFORM_WINDOWS) || defined(PLATFORM_LINUX)
		mInput = std::make_unique<InputImpl>();
		mTimer = std::make_unique<TimerImpl>();
		mWindow = std::make_unique<WindowImpl>();
#else
#error "Not Support Platform,only windows is available now!"
#endif

		Logger::GetInstance().Init();
		mInput->Init();
		mTimer->Init();

		GraphicsContext::GetInstance().Init();

		mSceneIdx = 0;
		mSceneRenderer.Init();
	}

	void App::Update()
	{
		mInput->PreUpdate();
		mWindow->PreUpdate();

		for (const auto &entity : mScenes[mSceneIdx]->GetAllEntities())
		{
			for (const auto &comp : entity->GetAllComponents())
			{
				comp->Update();
				comp->LateUpdate();
			}
		}

		mWindow->PostUpdate();
		mInput->PostUpdate();
	}
	void App::Render()
	{
		mSceneRenderer.Render(mScenes[mSceneIdx].get());
	}

	void App::RenderGizmo()
	{
	}

	void App::CleanUp()
	{
		GraphicsContext::GetInstance().Destroy();
	}
}