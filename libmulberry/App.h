#pragma once
#include <cstdint>
#include <string>
#include <memory>
#include <vector>
#include <SDL.h>
#include "Core/Singleton.h"
#include "Graphics/RHI/GraphicsContext.h"
#include "Graphics/SceneRenderer.h"
#include "Vec2.h"
#include "Scene.h"
#include "Platform/Timer.h"
#include "Platform/Window.h"
namespace mulberry
{
	enum class AppState
	{
		INIT,
		PROCESS_INPUT,
		UPDATE,
		DRAW,
		EXIT,
		PAUSE,
	};

	class App : public Singleton<App>
	{
	public:
		void Init();
		void Run();

		Scene *CreateScene(std::string_view name);
		Scene *GetScene(std::string_view name);
		bool RemoveScene(std::string_view name);
		void RemoveAllScenes();

		void Quit();

		void SetGraphicsBackend(GraphicsBackend graphicsBackend);
		GraphicsConfig &GetGraphicsConfig();

		Window *GetWindow() const;
		Input *GetInput() const;
		Timer *GetTimer() const;

		GraphicsContext *GetGraphicsContext() const;

	private:
		void PreUpdate();
		void Update();
		void Render();
		void RenderGizmo();
		void PostUpdate();
		void Destroy();

		AppState mState;

		std::unique_ptr<Window> mWindow;
		std::unique_ptr<Input> mInput;
		std::unique_ptr<Timer> mTimer;

		std::unique_ptr<GraphicsContext> mGraphicsContext;

		std::vector<std::unique_ptr<Scene>> mScenes;
		int32_t mSceneIdx;

		std::unique_ptr<SceneRenderer> mSceneRenderer;
	};
}