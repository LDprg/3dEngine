#include <any>
#include <numeric>

#include "Engine.hpp"

using namespace __XXECS;

class App final : public Application
{
protected:
    bool m_state = false;

public:
    auto Init() -> void override
    {
        GetClearColor() = {0.5f, 0.5f, 0.5f};

        {
            const auto entity = GetEntityManager().create();
            auto &item = GetEntityManager().emplace<Drawable>(entity, Drawable(Math::Vertices(3), Math::Indices(3)));
            item.indices = {0, 1, 2};

            item.vertices = {{Math::Position(-0.5, -0.5), Math::Color(1, 0, 0)},
                             {Math::Position(0.0, +0.5), Math::Color(0, 1, 0)},
                             {Math::Position(+0.5, -0.5), Math::Color(0, 0, 1)},};

            Drawable::Create(item);
        }

        {
            const auto entity = GetEntityManager().create();
            auto &item = GetEntityManager().emplace<Drawable>(entity, Drawable(Math::Vertices(3), Math::Indices(3)));
            item.indices = {0, 1, 2};

            item.vertices = {{Math::Position(+0.5, +0.5), Math::Color(1, 0, 0)},
                             {Math::Position(0.0, -0.5), Math::Color(0, 1, 0)},
                             {Math::Position(-0.5, +0.5), Math::Color(0, 0, 1)},};

            Drawable::Create(item);
        }
    }

    auto Event(const std::any &event) -> void override
    {
        if (Input::IsKeyPressed(Key::Escape))
            Close();

        if (event.type() == typeid(Event::KeyEvent))
        {
            const auto [key, action] = any_cast<Event::KeyEvent>(event);
            if (key == Key::F11 && action == Action::Press)
                GetWindow().SetFullscreen(!GetWindow().IsFullscreen());
        }
    }

    auto Update() -> void override
    {
        const auto view = GetEntityManager().view<Drawable>();

        view.each([this](auto &render)
        {
            for (unsigned int i = 0; i < render.vertices.size(); i++)
                render.vertices[i].color.a = m_state ? 0.5 : 1;
        });
    }

    auto ImGui() -> void override
    {
        if (ImGui::Button("Change"))
            m_state = !m_state;

        ImGui::ColorPicker4("Background Color", GetClearColor());
    }

    auto Render() -> void override
    {
        const auto view = GetEntityManager().view<Drawable>();
        for (const auto entity : view)
        {
            auto &item = view.get<Drawable>(entity);
            Drawable::Draw(item);
        }
    }

    auto Shutdown() -> void override
    {
    }
};


CREATE_APPLICATION(App)
