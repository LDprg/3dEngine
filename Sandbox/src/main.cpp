#include "Engine.hpp"

class App final : public Application
{
protected:
    bool m_size = false;
    bool m_transp = false;

public:
    auto Init() -> void override
    {
        GetClearColor() = {0.5f, 0.5f, 0.5f};

		{
            auto [entity, tri, draw] = GetEntityManager().CreateDynamicShape<Entity::Triangle>();
            tri.color = {0, 1, 0};
		}

        GetEntityManager().CreateShape<Entity::Circle>();

        {
            auto [entity,rec,draw] = GetEntityManager().CreateShape<Entity::Rectangle>();
            rec.width = 0.5f;
            rec.color = {0, 0, 1};
        }
    }

    auto Event(const std::any &event) -> void override
    {
        if (Input::IsKeyPressed(Key::Escape))
            Close();

        if (const auto keyEvent = any_cast<Event::KeyEvent>(&event))
            if (keyEvent->key == Key::F11 && keyEvent->action == Action::Press)
                GetWindow().SetFullscreen(!GetWindow().IsFullscreen());
    }

    auto Update() -> void override
    {
        const auto viewRec = GetEntityManager().view<Entity::Rectangle>();

        viewRec.each([this](auto &rec)
        {
            if (m_size)
                rec.width = 1.0f;
            else
                rec.width = 0.5f;
        });

        const auto viewTri = GetEntityManager().view<Entity::Triangle>();

        viewTri.each([this](const auto entity, auto &tri)
        {
            if (m_transp)
                tri.color.a = 0.5f;
            else
                tri.color.a = 1.f;

            GetEntityManager().emplace_or_replace<Entity::UpdateShapeTag>(entity);
        });

        GetEntityManager().UpdateDynamicShape<Entity::Rectangle>();
        GetEntityManager().UpdateShape<Entity::Triangle>();
        GetEntityManager().UpdateShape<Entity::Circle>();
    }

    auto ImGui() -> void override
    {
        if (ImGui::Button("Hide"))
            m_transp = !m_transp;

        ImGui::Spacing();

        if (ImGui::Button("Size"))
            m_size = !m_size;

        ImGui::Spacing();

        if (ImGui::Button("Remove"))
        {
            const auto view = GetEntityManager().view<Entity::Drawable>();
            GetEntityManager().destroy(view.front());
        }

        ImGui::Spacing();

        ImGui::ColorPicker4("Background Color", GetClearColor());
    }

    auto Render() -> void override
    {
        GetEntityManager().DrawShape();
    }

    auto Shutdown() -> void override
    {
    }
};

CREATE_APPLICATION(App);
