#pragma once

#include "Engine/Core/Application.hpp"

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

		Diligent::RefCntAutoPtr<Diligent::IDeviceContext>& GetNative()
		{
			return m_pImmediateContext;
		}

	private:
		Diligent::RefCntAutoPtr<Diligent::IDeviceContext> m_pImmediateContext;
	};
}
