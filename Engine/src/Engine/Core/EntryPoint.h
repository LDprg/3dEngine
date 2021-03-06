#pragma once

#include <Engine/Core/Application.h>
#include <Engine/Core/Log.h>

#define CREATE_APPLICATION(app) __XXECS::Application* __XXECS::CreateApplication() {return new app();}

namespace __XXECS
{
	extern Application* CreateApplication();
}

int main(int argc, char** argv)
{
	__XXECS::Log::Init();

	LOG_CORE_TRACE("CREATE APP");
	const auto app = __XXECS::CreateApplication();

	LOG_CORE_TRACE("RUN APP");
	app->RunLoop();

	LOG_CORE_TRACE("DELETE APP");
	delete app;
}
