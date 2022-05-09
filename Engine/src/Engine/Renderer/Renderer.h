#pragma once
#include <memory>

#include <ImGuiDiligentRenderer.hpp>
#include <Engine/Renderer/imgui.h>
#include <ThirdParty/imgui/backends/imgui_impl_glfw.h>
#include <TextureLoader/interface/Image.h>
#include <ScreenCapture.hpp>

#include "Engine/Renderer/SwapChain.h"

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
		~Renderer() = default;

		void Exit();

		void Bind(RenderArguments renderArgs);

		static void LoadShader(const char* filename);
	private:
		void ThreadInit(const RenderArguments* args);
		void ThreadUpdate();
		void ThreadExit();
		int32_t RunThread(const RenderArguments* userData);

		std::thread m_renderThread;
		RenderArguments m_renderArgs;
		
		Diligent::RefCntAutoPtr<Diligent::IPipelineState> m_pPSO;
		Diligent::RENDER_DEVICE_TYPE m_DeviceType = Diligent::RENDER_DEVICE_TYPE_D3D11;
	};
}
