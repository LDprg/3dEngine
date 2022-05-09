#pragma once

#include <ImGuiDiligentRenderer.hpp>
#include <SwapChain.h>
#include <Imgui/interface/ImGuiUtils.hpp>
#include <Imgui/interface/ImGuiImplDiligent.hpp>
#include <ThirdParty/imgui/imgui.h>

#include "backends/imgui_impl_glfw.h"
#include "Engine/Core/Application.h"
#include "Engine/Events/Event.h"

namespace __XXECS
{
	class ImguiManager
	{
	public:
		void Init();

		void Event(EventType* event) const;
		void NewFrame();
		void Render();

		void Destory();
	private:
		std::unique_ptr<Diligent::ImGuiDiligentRenderer> m_pImgui;
	};
}
