#pragma once

#include <Engine/Renderer/imgui.h>

namespace __XXECS
{
	struct RenderArguments
	{
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

		static void Renderer::LoadShader(const char* filename);
	private:
		static void ThreadInit(const RenderArguments* args);
		static void ThreadUpdate();
		static void ThreadExit();

		static int32_t RunThread(const RenderArguments* userData);

		std::thread m_renderThread;
		RenderArguments m_renderArgs;
	};
}
