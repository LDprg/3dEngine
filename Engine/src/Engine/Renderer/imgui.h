#pragma once

#include <ImGuiDiligentRenderer.hpp>
#include <SwapChain.h>
#include <Imgui/interface/ImGuiImplDiligent.hpp>
#include <Imgui/interface/ImGuiUtils.hpp>
#include <ThirdParty/imgui/imgui.h>

#include "backends/imgui_impl_glfw.h"
#include "Engine/Core/Application.h"
#include "Engine/Events/Event.h"

namespace __XXECS
{
	class ImGuiManager
	{
	public:
		void Init();

		void Event(const std::any& ev) const;
		void NewFrame();
		void Render();

		void Destroy();

	private:
		std::unique_ptr<Diligent::ImGuiDiligentRenderer> m_pImGui;
	};
}
