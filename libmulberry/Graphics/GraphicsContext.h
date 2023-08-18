#pragma once
#include <memory>
#include <mutex>
#include "Vec2.h"
#include "Core/Singleton.h"

namespace mulberry
{
	enum class GraphicsBackend
	{
		GL,
		VK,
	};

	enum class MsaaLevel
	{
		NONE,
		X2,
		X4,
		X8,
		X16,
		X32,
		X64,
	};

	struct GraphicsConfig
	{
		GraphicsBackend backend = GraphicsBackend::GL;
		bool useVSync = false;
		bool useDoubleBuffer = true;
		MsaaLevel msaaLevel=MsaaLevel::NONE;
	};

	class GraphicsContext : public Singleton<GraphicsContext>
	{
	public:
		void Init();
		void Destroy();

		void BeginFrame();
		void EndFrame();
	};
}