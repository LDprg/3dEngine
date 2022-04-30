#include "pch.hpp"
#include "Application.h"

__XXECS::Application::Application(const char* _name, const char* _description, const char* _url)
	: entry::AppI(_name, _description, _url)
{
}

__XXECS::Application::~Application()
{
}
