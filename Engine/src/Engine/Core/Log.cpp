#include "Log.hpp"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace __XXECS
{
    std::shared_ptr<spdlog::logger> Log::m_coreLogger;
    std::shared_ptr<spdlog::logger> Log::m_clientLogger;

    auto Log::Init() -> void
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");

        m_coreLogger = spdlog::stdout_color_mt("CORE");
        m_coreLogger->set_level(spdlog::level::trace);

        m_clientLogger = spdlog::stdout_color_mt("APP");
        m_clientLogger->set_level(spdlog::level::trace);
    }
}
