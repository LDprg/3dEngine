/*****************************************************************/ /**
 * \file   Log.hpp
 * \brief  Log class, defines Logging Tools
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#pragma once

#pragma warning(push)
#pragma warning(disable:4189)
#include <spdlog/spdlog.h>
#pragma warning(pop)

namespace __XXECS
{
    class Log
    {
    public:
        static auto Init() -> void;

        static auto GetCoreLogger() -> std::shared_ptr<spdlog::logger>&
        {
            return m_coreLogger;
        }

        static auto GetClientLogger() -> std::shared_ptr<spdlog::logger>&
        {
            return m_clientLogger;
        }

    private:
        static std::shared_ptr<spdlog::logger> m_coreLogger;
        static std::shared_ptr<spdlog::logger> m_clientLogger;
    };
}

#ifdef ENGINE_PLATFORM_WINDOWS
#define DEBUG_BREAK() __debugbreak()
#else
#define DEBUG_BREAK()
#endif

#define LOG_CORE_DEBUG(...)	::__XXECS::Log::GetCoreLogger()->debug(__VA_ARGS__)
#define LOG_CORE_TRACE(...)	::__XXECS::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LOG_CORE_INFO(...)	::__XXECS::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LOG_CORE_WARN(...)	::__XXECS::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LOG_CORE_ERROR(...)	::__XXECS::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LOG_CORE_FATAL(...)	::__XXECS::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define LOG_CORE_ASSERT(x, ...) {if(!(x)){LOG_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); DEBUG_BREAK();}}

#define LOG_CLIENT_DEBUG(...)		::__XXECS::Log::GetClientLogger()->debug(__VA_ARGS__)
#define LOG_CLIENT_TRACE(...)		::__XXECS::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LOG_CLIENT_INFO(...)		::__XXECS::Log::GetClientLogger()->info(__VA_ARGS__)
#define LOG_CLIENT_WARN(...)		::__XXECS::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LOG_CLIENT_ERROR(...)		::__XXECS::Log::GetClientLogger()->error(__VA_ARGS__)
#define LOG_CLIENT_FATAL(...)		::__XXECS::Log::GetClientLogger()->critical(__VA_ARGS__)
#define	LOG_CLIENT_ASSERT(x, ...)	{if(!(x)){LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); DEBUG_BREAK();}}
