#include "Engine.hpp"

class App final : public Application
{
protected:
    bool m_state = false;

public:
    auto Init() -> void override
    {
        GetClearColor() = {0.5f, 0.5f, 0.5f};

        {
            const auto entity = GetEntityManager().CreateEntity();
            auto &item = GetEntityManager().AddComponent<Entity::Drawable>(
                entity, Entity::Drawable(Math::Vertices(3), Math::Indices{0, 1, 2}));

            item.vertices = {{Math::Position(-0.5, -0.5), Math::Color(1, 0, 0)},
                             {Math::Position(0.0, +0.5), Math::Color(0, 1, 0)},
                             {Math::Position(+0.5, -0.5), Math::Color(0, 0, 1)},};
        }

        {
            const auto entity = GetEntityManager().CreateEntity();
            auto &item = GetEntityManager().AddComponent<Entity::Drawable>(
                entity, Entity::Drawable(Math::Vertices(3), Math::Indices{0, 1, 2}));

            item.vertices = {{Math::Position(+0.5, +0.5), Math::Color(1, 0, 0)},
                             {Math::Position(0.0, -0.5), Math::Color(0, 1, 0)},
                             {Math::Position(-0.5, +0.5), Math::Color(0, 0, 1)},};
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
        const auto view = GetEntityManager().GetEntities<Entity::Drawable>();

        view.each([this](auto &render)
        {
            for (unsigned int i = 0; i < render.vertices.size(); i++)
                render.vertices[i].color.a = m_state ? 0 : 1;
        });
    }

    auto ImGui() -> void override
    {
        if (ImGui::Button("Hide"))
            m_state = !m_state;

        ImGui::Spacing();

        if (ImGui::Button("Remove"))
        {
            const auto view = GetEntityManager().GetEntities<Entity::Drawable>();
            GetEntityManager().RemoveComponent<Entity::Drawable>(view.front());
        }

        ImGui::Spacing();

        ImGui::ColorPicker4("Background Color", GetClearColor());
    }

    auto Render() -> void override
    {
        const auto view = GetEntityManager().GetEntities<Entity::Drawable>();
        for (auto [entity, drawable] : view.each())
            Entity::Drawable::Draw(drawable);
    }

    auto Shutdown() -> void override
    {
    }
};


CREATE_APPLICATION(App)
