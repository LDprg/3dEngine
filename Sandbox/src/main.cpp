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
            auto [entity,rec,draw] = GetEntityManager().CreateShape<Entity::Rectangle>();
			rec.width = 0.5f;
        }

		GetEntityManager().CreateShape<Entity::Triangle>();
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
        const auto viewRec = GetEntityManager().view<Entity::Rectangle, Entity::Drawable>();

        viewRec.each([this](auto &shape, auto &draw)
        {
            Entity::Rectangle::Update(shape, draw);
        });

        const auto viewTri = GetEntityManager().view<Entity::Triangle, Entity::Drawable>();

        viewTri.each([this](auto &shape, auto &draw)
        {
            Entity::Triangle::Update(shape, draw);
        });

        const auto viewDraw = GetEntityManager().view<Entity::Drawable>();

        viewDraw.each([this](auto &draw)
        {
            for (unsigned int i = 0; i < draw.vertices.size(); i++)
                draw.vertices[i].color.a = m_state ? 0 : 1;
        });
    }

    auto ImGui() -> void override
    {
        if (ImGui::Button("Hide"))
            m_state = !m_state;

        ImGui::Spacing();

        if (ImGui::Button("Remove"))
        {
            const auto view = GetEntityManager().view<Entity::Drawable>();
            GetEntityManager().remove<Entity::Drawable>(view.front());
        }

        ImGui::Spacing();

        ImGui::ColorPicker4("Background Color", GetClearColor());
    }

    auto Render() -> void override
    {
        const auto view = GetEntityManager().view<Entity::Drawable>();
        for (auto [entity, drawable] : view.each())
            Entity::Drawable::Draw(drawable);
    }

    auto Shutdown() -> void override
    {
    }
};


CREATE_APPLICATION(App)
