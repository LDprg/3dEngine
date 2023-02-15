/*****************************************************************/ /**
 * \file   imgui.hpp
 * \brief  ImGui manager
 * 
 * \author LD
 * \date   February 2023
 *********************************************************************/
#pragma once

#include <Imgui/interface/ImGuiDiligentRenderer.hpp>

namespace __XXECS
{
    class ImGuiManager
    {
    public:
        auto Init() -> void;

        auto Event(const std::any &ev) const -> void;
        auto NewFrame() const -> void;
        auto Render() const -> void;

        auto Destroy() const -> void;

    private:
        std::unique_ptr<Diligent::ImGuiDiligentRenderer> m_pImGui;
    };
}
