#pragma once
#include <SwapChain.h>
#include <Common/interface/RefCntAutoPtr.hpp>

#include "Engine/Core/Application.hpp"

namespace __XXECS
{
	class SwapChain
	{
	public:
		SwapChain() = default;

		~SwapChain()
		{
			m_pSwapChain.Release();
		}

		Diligent::RefCntAutoPtr<Diligent::ISwapChain>& GetNative()
		{
			return m_pSwapChain;
		}

		const Diligent::SwapChainDesc& GetDesc()
		{
			return m_pSwapChain->GetDesc();
		}

		void Present(UINT32 SyncInterval = 1)
		{
			return m_pSwapChain->Present(SyncInterval);
		}

	private:
		Diligent::RefCntAutoPtr<Diligent::ISwapChain> m_pSwapChain;
	};
}
