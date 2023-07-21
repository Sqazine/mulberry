#pragma once
#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <string>
#include "Singleton.h"
namespace mulberry
{
	class Logger : public Singleton<Logger>
	{
	public:
		void Init();

		spdlog::logger *GetCoreLogger();
		spdlog::logger *GetClientLogger();

	private:
		std::shared_ptr<spdlog::logger> sCoreLogger;
		std::shared_ptr<spdlog::logger> sClientLogger;
	};
}

#define MULBERRY_CORE_ERROR(...) ::mulberry::Logger::GetInstance().GetCoreLogger()->error(__VA_ARGS__)
#define MULBERRY_CORE_WARN(...) ::mulberry::Logger::GetInstance().GetCoreLogger()->warn(__VA_ARGS__)
#define MULBERRY_CORE_INFO(...) ::mulberry::Logger::GetInstance().GetCoreLogger()->info(__VA_ARGS__)
#define MULBERRY_CORE_TRACE(...) ::mulberry::Logger::GetInstance().GetCoreLogger()->trace(__VA_ARGS__)
#define MULBERRY_CORE_FATAL(...) ::mulberry::Logger::GetInstance().GetCoreLogger()->fatal(__VA_ARGS__)

#define MULBERRY_ERROR(...) ::mulberry::Logger::GetInstance().GetClientLogger()->error(__VA_ARGS__)
#define MULBERRY_WARN(...) ::mulberry::Logger::GetInstance().GetClientLogger()->warn(__VA_ARGS__)
#define MULBERRY_INFO(...) ::mulberry::Logger::GetInstance().GetClientLogger()->info(__VA_ARGS__)
#define MULBERRY_TRACE(...) ::mulberry::Logger::GetInstance().GetClientLogger()->trace(__VA_ARGS__)
#define MULBERRY_FATAL(...) ::mulberry::Logger::GetInstance().GetClientLogger()->fatal(__VA_ARGS__)