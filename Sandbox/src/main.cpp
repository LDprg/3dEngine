#include "Engine.hpp"

using namespace XXECS;

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
            const auto entity = GetEntityManager().CreateShape<Entity::Triangle, Entity::TriangleSystem>();
            GetEntityManager().get<Entity::Color>(entity).color = {0, 1, 0};
        }


        {
            const auto entity = GetEntityManager().CreateShape<Entity::Circle, Entity::CircleSystem>();
            GetEntityManager().get<Entity::Position>(entity).position = {0.5f, 0.5f};
        }

        {
            const auto entity = GetEntityManager().CreateDynamicShape<Entity::Rectangle, Entity::RectangleSystem>();
            GetEntityManager().get<Entity::Rectangle>(entity).width = 0.5f;
            GetEntityManager().get<Entity::Color>(entity).color = {0, 0, 1};
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

    auto Update(float deltaTime) -> void override
    {
        static auto time = 0.f;
        time += deltaTime;
        if (time > 1.f)
        {
            Log::Info("FPS: {}", 1.f / deltaTime);
            time = 0.f;
        }

        const auto viewRec = GetEntityManager().view<Entity::Rectangle>();

        viewRec.each([this, &deltaTime](auto &rec)
        {
            if (m_size)
                rec.width += 0.1f * deltaTime;
            else
                rec.width -= 0.1f * deltaTime;
        });

        const auto viewTri = GetEntityManager().view<Entity::Triangle, Entity::Color>();

        viewTri.each([this](const auto entity, auto &, auto &col)
        {
            if (m_transp)
                col.color.a = 0.5f;
            else
                col.color.a = 1.f;

            GetEntityManager().emplace_or_replace<Entity::UpdateShapeTag>(entity);
        });

        GetEntityManager().UpdateDynamicShape<Entity::Rectangle, Entity::RectangleSystem>();
        GetEntityManager().UpdateShape<Entity::Triangle, Entity::TriangleSystem>();
        GetEntityManager().UpdateShape<Entity::Circle, Entity::CircleSystem>();
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
        GetEntityManager().DrawDynamicShape();
        GetEntityManager().DrawShape();
    }

    auto Shutdown() -> void override
    {
    }
};

auto main() -> int
{
    XXECS::CreateApplication<App>();
}
