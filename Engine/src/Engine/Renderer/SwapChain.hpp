#pragma once
#include <SwapChain.h>
#include <Common/interface/RefCntAutoPtr.hpp>

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

		auto GetNative() -> Diligent::RefCntAutoPtr<Diligent::ISwapChain>&
		{
			return m_pSwapChain;
		}

		auto GetDesc() -> const Diligent::SwapChainDesc&
		{
			return m_pSwapChain->GetDesc();
		}

		auto Present(UINT32 SyncInterval = 1) -> void
		{
			return m_pSwapChain->Present(SyncInterval);
		}

	private:
		Diligent::RefCntAutoPtr<Diligent::ISwapChain> m_pSwapChain;
	};
}
