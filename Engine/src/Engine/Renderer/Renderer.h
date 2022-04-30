#pragma once

#include <bgfx/bgfx.h>
#include <bx/bx.h>
#include <bx/thread.h>

#include <common/imgui/imgui.h>

namespace __XXECS
{
	struct RenderArguments
	{
		bgfx::PlatformData platformData;
		uint32_t width;
		uint32_t height;
	};

	class Renderer
	{
	public:
		Renderer()
		{
		}

		virtual ~Renderer()
		{
		}

		void Init();
		void Exit();

		void Update();

		void Bind(RenderArguments renderArgs);

	private:
		static int32_t runThread(bx::Thread* self, void* userData);

		bx::Thread m_renderThread;
		RenderArguments m_renderArgs;
	};
}
