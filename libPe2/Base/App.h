#pragma once
#include <cstdint>
#include <string>
#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include "../Render/RenderContext.h"
#include "../Math/Vec2.h"
#include "../Scene/Scene.h"
#include "Timer.h"
namespace Pe2
{

	enum class AppState
	{
		INIT,
		PROCESS_INPUT,
		UPDATE,
		DRAW,
		EXIT
	};

	class App
	{
	public:
		static void Init(const RenderContextInfo& info);
		static void Run();

		static Scene* CreateScene(std::string_view name);
		static Scene* GetScene(std::string_view name);
		static bool RemoveScene(std::string_view name);
		static void RemoveAllScenes();

		static void Quit();

		static void SetWindowExtent(const Vec2& extent);
		static Vec2 GetWindowExtent();

	private:
		static void ProcessInput();
		static void Update();
		static void Render();
		static void RenderGizmo();
		static void RenderUI();
		static void CleanUp();

		static AppState mState;
		static Input mInput;
		static Timer mTimer;

		static std::vector<std::unique_ptr<Scene>> mScenes;
		static int32_t mSceneIdx;

		static SceneRenderer mSceneRenderer;
	};
}