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

#define MULBERRY_CORE_ERROR(...)                                               \
	do                                                                         \
	{                                                                          \
		spdlog::error("{},{}:", __FILE__, __LINE__);                           \
		::mulberry::Logger::GetInstance().GetCoreLogger()->error(__VA_ARGS__); \
		abort();                                                               \
	} while (false);

#define MULBERRY_CORE_WARN(...)                                               \
	do                                                                        \
	{                                                                         \
		spdlog::warn("{},{}:", __FILE__, __LINE__);                           \
		::mulberry::Logger::GetInstance().GetCoreLogger()->warn(__VA_ARGS__); \
	} while (false);

#define MULBERRY_CORE_INFO(...) ::mulberry::Logger::GetInstance().GetCoreLogger()->info(__VA_ARGS__)

#define MULBERRY_ERROR(...) ::mulberry::Logger::GetInstance().GetClientLogger()->error(__VA_ARGS__)
#define MULBERRY_WARN(...) ::mulberry::Logger::GetInstance().GetClientLogger()->warn(__VA_ARGS__)
#define MULBERRY_INFO(...) ::mulberry::Logger::GetInstance().GetClientLogger()->info(__VA_ARGS__)