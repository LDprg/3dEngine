#pragma once

#include <Imgui/interface/ImGuiImplDiligent.hpp>

#include <ImGuiDiligentRenderer.hpp>
#include <ThirdParty/imgui/imgui.h>

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
