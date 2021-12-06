#pragma once
#include <cstdint>
#include <string>
#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include "../Math/Vec2.h"
#include "../Scene/Scene.h"

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
		static void Run();

		static Scene* CreateScene(std::string_view name);
		static bool RemoveScene(std::string_view name);
		static void RemoveAllScenes();

		static void Quit();

	private:
		static void Init();
		static void ProcessInput();
		static void Update();
		static void Draw();
		static void CleanUp();

		static AppState m_State;

		static std::vector<std::unique_ptr<Scene>> m_Scenes;
	};
}