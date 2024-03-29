/*****************************************************************/ /**
 * \file   SwapChain.hpp
 * \brief  SwapChain management
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#pragma once

#include <Common/interface/RefCntAutoPtr.hpp>
#include <Graphics/GraphicsEngine/interface/SwapChain.h>

namespace XXECS
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

        auto Present(Diligent::Uint32 SyncInterval = 1) -> void
        {
            return m_pSwapChain->Present(SyncInterval);
        }

    private:
        Diligent::RefCntAutoPtr<Diligent::ISwapChain> m_pSwapChain;
    };
}
