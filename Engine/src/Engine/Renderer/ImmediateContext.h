#pragma once

#include "Engine/Core/Application.h"

namespace __XXECS
{
	class ImmediateContext
	{
	public:
		Diligent::RefCntAutoPtr<Diligent::IDeviceContext>& GetNative()
		{
			return m_pImmediateContext;
		}

	private:
		Diligent::RefCntAutoPtr<Diligent::IDeviceContext> m_pImmediateContext;
	};
}
