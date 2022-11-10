#include "Log.h"
namespace mulberry
{
	std::shared_ptr<spdlog::logger> Log::sCoreLogger;
	std::shared_ptr<spdlog::logger> Log::sClientLogger;

	void Log::Init(const std::string& clientName)
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		sCoreLogger = spdlog::stdout_color_mt("mulberry");
		sCoreLogger->set_level(spdlog::level::trace);

		sClientLogger = spdlog::stdout_color_mt(clientName);
		sClientLogger->set_level(spdlog::level::trace);
	}
}