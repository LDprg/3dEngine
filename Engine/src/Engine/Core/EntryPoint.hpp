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

namespace XXECS
{
    template<typename T> concept ApplicationConcept = requires() { std::derived_from<T, Application>; };

    template<ApplicationConcept T>
    auto CreateApplication() -> void
    {
        Log::Log::Init();

        Log::CoreTrace("CREATE APP");
        T app;

        Log::CoreTrace("RUN APP");
        app.RunLoop();

        Log::CoreTrace("DELETE APP");
    }
}
