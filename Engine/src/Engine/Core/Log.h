#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace __XXECS
{
	class Log
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& GetCoreLogger()
		{
			return s_CoreLogger;
		}

		static std::shared_ptr<spdlog::logger>& GetClientLogger()
		{
			return s_ClientLogger;
		}

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

#define LOG_CORE_DEBUG(...)	::__XXECS::Log::GetCoreLogger()->debug(__VA_ARGS__)
#define LOG_CORE_TRACE(...)	::__XXECS::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LOG_CORE_INFO(...)	::__XXECS::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LOG_CORE_WARN(...)	::__XXECS::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LOG_CORE_ERROR(...)	::__XXECS::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LOG_CORE_FATAL(...)	::__XXECS::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define LOG_CORE_ASSERT(x, ...) {if(!(x)){LOG_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}

#define LOG_DEBUG(...)		::__XXECS::Log::GetClientLogger()->debug(__VA_ARGS__)
#define LOG_TRACE(...)		::__XXECS::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)		::__XXECS::Log::GetClientLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)		::__XXECS::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)		::__XXECS::Log::GetClientLogger()->error(__VA_ARGS__)
#define LOG_FATAL(...)		::__XXECS::Log::GetClientLogger()->critical(__VA_ARGS__)
#define	LOG_ASSERT(x, ...)	{if(!(x)){LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
