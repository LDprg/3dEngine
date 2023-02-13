#pragma once

#include <Imgui/interface/ImGuiImplDiligent.hpp>
#include <Imgui/interface/ImGuiUtils.hpp>

#include <ImGuiDiligentRenderer.hpp>
#include <ThirdParty/imgui/imgui.h>

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
