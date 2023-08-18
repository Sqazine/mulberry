#include "App.h"
#include "SceneRenderer.h"
#include "GraphicsContext.h"
#include "Logger.h"
namespace mulberry
{
	void App::Run()
	{
		mWindow->Show();
		while (mState != AppState::EXIT)
		{
			mTimer.Update();
			ProcessInput();
			Update();
			GraphicsContext::GetInstance().BeginFrame();
			Render();
			RenderGizmo();
			RenderUI();
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
		mGraphicsConfig.backend = graphicsBackend;
	}

	const GraphicsConfig &App::GetGraphicsConfig() const
	{
		return mGraphicsConfig;
	}

	Window *App::GetWindow() const
	{
		return mWindow.get();
	}

	void App::Init()
	{
		mWindow = std::make_unique<Window>();

		Logger::GetInstance().Init();
		mInput.Init();
		mTimer.Init();

		GraphicsContext::GetInstance().Init();

		mSceneIdx = 0;
		mSceneRenderer.Init();
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
		GraphicsContext::GetInstance().Destroy();
	}
}