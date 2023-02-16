/*****************************************************************/ /**
 * \file   EntryPoint.hpp
 * \brief  Defines the entry point for the application
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#pragma once

#include <Engine/Core/Application.hpp>
#include <Engine/Core/Log.hpp>

namespace __XXECS
{
    extern auto CreateApplication() -> Application *;
}

auto main() -> int
{
    __XXECS::Log::Log::Init();

    __XXECS::Log::CoreTrace("CREATE APP");
    const auto app = __XXECS::CreateApplication();

    __XXECS::Log::CoreTrace("RUN APP");
    app->RunLoop();

    __XXECS::Log::CoreTrace("DELETE APP");
    delete app;
}
