#include "Logger.h"
namespace mulberry
{
	void Logger::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		sCoreLogger = spdlog::stdout_color_mt("mulberry");
		sCoreLogger->set_level(spdlog::level::trace);

		sClientLogger = spdlog::stdout_color_mt("GameApp");
		sClientLogger->set_level(spdlog::level::trace);
	}

	spdlog::logger *Logger::GetCoreLogger()
	{
		return sCoreLogger.get();
	}

	spdlog::logger *Logger::GetClientLogger()
	{
		return sClientLogger.get();
	}

}