#pragma once

#include "Window.h"
#include "Engine/Events/Event.h"
#include "Engine/Events/Input.h"

#include <common/common.h>

#define CREATE_APP(app, ...) ENTRY_IMPLEMENT_MAIN(app, __VA_ARGS__);

namespace __XXECS
{
	class Application : public entry::AppI
	{
	public:
		Application(const char* _name, const char* _description, const char* _url);
		virtual ~Application();

		virtual void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) = 0;
		virtual int shutdown() = 0;
		virtual bool update() = 0;
	};
}
