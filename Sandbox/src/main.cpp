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
			auto& item = GetEntityManager().emplace<Renderable>(entity, Renderable(Vertices(3), Indices(3)));
			item.Indices = {0, 1, 2};

			item.Vertices = {
				{Position(-0.5, -0.5), Color(1, 0, 0)}, {Position(0.0, +0.5), Color(0, 1, 0)},
				{Position(+0.5, -0.5), Color(0, 0, 1)},
			};

			Renderable::Create(item);
		}

		{
			const auto entity = GetEntityManager().create();
			auto& item = GetEntityManager().emplace<Renderable>(entity, Renderable(Vertices(3), Indices(3)));
			item.Indices = {0, 1, 2};

			item.Vertices = {
				{Position(+0.5, +0.5), Color(1, 0, 0)}, {Position(0.0, -0.5), Color(0, 1, 0)},
				{Position(-0.5, +0.5), Color(0, 0, 1)},
			};

			Renderable::Create(item);
		}
	}

	auto Event(const std::any& event) -> void override
	{
		if (Input::IsKeyPressed(Key::Escape))
			Close();

		if (event.type() == typeid(KeyEvent))
		{
			const auto [key, action] = any_cast<KeyEvent>(event);
			if (key == Key::F11 && action == Action::Press)
				GetWindow().SetFullscreen(!GetWindow().IsFullscreen());
		}
	}

	auto Update() -> void override
	{
		const auto view = GetEntityManager().view<Renderable>();

		view.each([this](auto& render)
		{
			for (unsigned int i = 0; i < render.Vertices.size(); i++)
				render.Vertices[i].color.a = m_state ? 0.5 : 1;
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
		const auto view = GetEntityManager().view<Renderable>();
		for (const auto entity : view)
		{
			auto& item = view.get<Renderable>(entity);
			Renderable::Draw(item);
		}
	}

	auto Shutdown() -> void override
	{
	}
};


CREATE_APPLICATION(App)
