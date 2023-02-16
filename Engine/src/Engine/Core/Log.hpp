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

namespace __XXECS::Log
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

#ifdef ENGINE_PLATFORM_WINDOWS
    template<typename... Args>
    auto DebugBreak(Args &&... args) -> decltype(__debugbreak(std::forward<Args>(args)...))
    {
        return __debugbreak(std::forward<Args>(args)...);
    }
#else
    template<typename... Args>
    auto DebugBreak(Args &&...args)
    {
    }
#endif

    template<typename... Args>
    constexpr auto CoreDebug(spdlog::format_string_t<Args...> fmt, Args &&... args) -> void
    {
        return Log::GetCoreLogger()->debug(std::forward<spdlog::format_string_t<Args...>>(fmt),
                                           std::forward<Args>(args)...);
    }

    template<typename... Args>
    constexpr auto CoreTrace(spdlog::format_string_t<Args...> fmt, Args &&... args) -> void
    {
        return Log::GetCoreLogger()->trace(std::forward<spdlog::format_string_t<Args...>>(fmt),
                                           std::forward<Args>(args)...);
    }

    template<typename... Args>
    constexpr auto CoreInfo(spdlog::format_string_t<Args...> fmt, Args &&... args) -> void
    {
        return Log::GetCoreLogger()->info(std::forward<spdlog::format_string_t<Args...>>(fmt),
                                          std::forward<Args>(args)...);
    }

    template<typename... Args>
    constexpr auto CoreWarn(spdlog::format_string_t<Args...> fmt, Args &&... args) -> void
    {
        return Log::GetCoreLogger()->warn(std::forward<spdlog::format_string_t<Args...>>(fmt),
                                          std::forward<Args>(args)...);
    }

    template<typename... Args>
    constexpr auto CoreError(spdlog::format_string_t<Args...> fmt, Args &&... args) -> void
    {
        return Log::GetCoreLogger()->error(std::forward<spdlog::format_string_t<Args...>>(fmt),
                                           std::forward<Args>(args)...);
    }

    template<typename... Args>
    constexpr auto CoreFatal(spdlog::format_string_t<Args...> fmt, Args &&... args) -> void
    {
        return Log::GetCoreLogger()->critical(std::forward<spdlog::format_string_t<Args...>>(fmt),
                                              std::forward<Args>(args)...);
    }

    template<typename Cond, typename... Args>
    constexpr auto CoreAssert(Cond &&cond, Args &&... args) -> void
    {
        if (!cond)
        {
            CoreError("Assertion Failed: {0}", std::forward<Args>(args)...);
            DebugBreak();
        }
    }

    template<typename... Args>
    constexpr auto Debug(spdlog::format_string_t<Args...> fmt, Args &&... args) -> void
    {
        return Log::GetClientLogger()->debug(std::forward<spdlog::format_string_t<Args...>>(fmt),
                                             std::forward<Args>(args)...);
    }

    template<typename... Args>
    constexpr auto Trace(spdlog::format_string_t<Args...> fmt, Args &&... args) -> void
    {
        return Log::GetClientLogger()->trace(std::forward<spdlog::format_string_t<Args...>>(fmt),
                                             std::forward<Args>(args)...);
    }

    template<typename... Args>
    constexpr auto Info(spdlog::format_string_t<Args...> fmt, Args &&... args) -> void
    {
        return Log::GetClientLogger()->info(std::forward<spdlog::format_string_t<Args...>>(fmt),
                                            std::forward<Args>(args)...);
    }

    template<typename... Args>
    constexpr auto Warn(spdlog::format_string_t<Args...> fmt, Args &&... args) -> void
    {
        return Log::GetClientLogger()->warn(std::forward<spdlog::format_string_t<Args...>>(fmt),
                                            std::forward<Args>(args)...);
    }

    template<typename... Args>
    constexpr auto Error(spdlog::format_string_t<Args...> fmt, Args &&... args) -> void
    {
        return Log::GetClientLogger()->error(std::forward<spdlog::format_string_t<Args...>>(fmt),
                                             std::forward<Args>(args)...);
    }

    template<typename... Args>
    constexpr auto Fatal(spdlog::format_string_t<Args...> fmt, Args &&... args) -> void
    {
        return Log::GetClientLogger()->critical(std::forward<spdlog::format_string_t<Args...>>(fmt),
                                                std::forward<Args>(args)...);
    }

    template<typename Cond, typename... Args>
    constexpr auto Assert(Cond &&cond, Args &&... args) -> void
    {
        if (!cond)
        {
            LogError("Assertion Failed: {0}", std::forward<Args>(args)...);
            DebugBreak();
        }
    }
}
