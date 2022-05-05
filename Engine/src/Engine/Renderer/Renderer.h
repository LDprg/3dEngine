#pragma once

#include <bgfx/bgfx.h>
#include <bx/thread.h>

namespace __XXECS
{
	struct RenderArguments
	{
		bgfx::PlatformData platformData;
		uint32_t width;
		uint32_t height;
	};

	class Renderer final
	{
	public:
		Renderer() = default;
		virtual ~Renderer() = default;

		void Exit();

		void Bind(RenderArguments renderArgs);

		static bgfx::ViewId GetView() { return kClearView; }

		static bgfx::ShaderHandle Renderer::LoadShader(const char* filename);
	private:
		static void ThreadInit(const RenderArguments* args);
		static void ThreadUpdate();
		static void ThreadExit();

		static int32_t RunThread(bx::Thread* self, void* userData);

		bx::Thread m_renderThread;
		RenderArguments m_renderArgs;
		static constexpr bgfx::ViewId kClearView = 0;
	};
}
