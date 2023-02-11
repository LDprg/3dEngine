#pragma once

namespace __XXECS
{
	class SwapChain
	{
	public:
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
