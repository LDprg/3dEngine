#pragma once

#include <ImGuiDiligentRenderer.hpp>
#include <TextureLoader/interface/Image.h>

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

		~Renderer()
		{
			m_pPSO.Release();
			m_pSRB.Release();
			m_VSConstants.Release();
		}

		void Exit();

		void Bind(RenderArguments renderArgs);

		Diligent::RefCntAutoPtr<Diligent::IPipelineState>& GetPipelineState()
		{
			return m_pPSO;
		}

		Diligent::RefCntAutoPtr<Diligent::IShaderResourceBinding>& GetShaderResourceBinding()
		{
			return m_pSRB;
		}

	private:
		void ThreadInit(const RenderArguments* args);
		void ThreadUpdate();
		void ThreadExit();
		int32_t RunThread(const RenderArguments* userData);

		std::thread m_renderThread;
		RenderArguments m_renderArgs;

		Diligent::RefCntAutoPtr<Diligent::IPipelineState> m_pPSO;
		Diligent::RefCntAutoPtr<Diligent::IShaderResourceBinding> m_pSRB;
		Diligent::RefCntAutoPtr<Diligent::IBuffer> m_VSConstants;
		Diligent::RENDER_DEVICE_TYPE m_DeviceType = Diligent::RENDER_DEVICE_TYPE_D3D12;
	};
}
