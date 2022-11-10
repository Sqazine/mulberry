#pragma once
#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <string>
namespace mulberry
{
	class Log
	{
	public:
		static void Init(const std::string& clientName);

		inline static std::shared_ptr<spdlog::logger> &GetCoreLogger()
		{
			return sCoreLogger;
		}

		inline static std::shared_ptr<spdlog::logger> &GetClientLogger()
		{
			return sClientLogger;
		}

	private:
		static std::shared_ptr<spdlog::logger> sCoreLogger;
		static std::shared_ptr<spdlog::logger> sClientLogger;
	};
}

#define MULBERRY_CORE_ERROR(...) ::mulberry::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MULBERRY_CORE_WARN(...) ::mulberry::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MULBERRY_CORE_INFO(...) ::mulberry::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MULBERRY_CORE_TRACE(...) ::mulberry::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MULBERRY_CORE_FATAL(...) ::mulberry::Log::GetCoreLogger()->fatal(__VA_ARGS__)

#define MULBERRY_ERROR(...) ::mulberry::Log::GetClientLogger()->error(__VA_ARGS__)
#define MULBERRY_WARN(...) ::mulberry::Log::GetClientLogger()->warn(__VA_ARGS__)
#define MULBERRY_INFO(...) ::mulberry::Log::GetClientLogger()->info(__VA_ARGS__)
#define MULBERRY_TRACE(...) ::mulberry::Log::GetClientLogger()->trace(__VA_ARGS__)
#define MULBERRY_FATAL(...) ::mulberry::Log::GetClientLogger()->fatal(__VA_ARGS__)