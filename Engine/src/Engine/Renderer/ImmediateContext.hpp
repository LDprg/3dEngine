/*****************************************************************/ /**
 * \file   ImmediateContext.hpp
 * \brief  ImmediateContext management
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#pragma once

namespace __XXECS
{
    class ImmediateContext
    {
    public:
        ImmediateContext() = default;

        ~ImmediateContext()
        {
            m_pImmediateContext.Release();
        }

        auto GetNative() -> Diligent::RefCntAutoPtr<Diligent::IDeviceContext>&
        {
            return m_pImmediateContext;
        }

    private:
        Diligent::RefCntAutoPtr<Diligent::IDeviceContext> m_pImmediateContext;
    };
}