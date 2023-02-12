#include <numeric>
#include <string>
#include <Engine/Entity/Components/Renderable.hpp>
#include <entt/entt.hpp>
#include <glm/glm.hpp>
#include <Graphics/GraphicsTools/interface/MapHelper.hpp>

#include "Engine.h"

using namespace __XXECS;

class App final : public Application
{
protected:
	bool state = false;

public:
	App() = default;

	~App() override = default;

	void Init() override
	{
		GetClearColor() = {0.5f, 0.5f, 0.5f};

		{
			const auto entity = GetEntityManager().create();
			auto& item = GetEntityManager().emplace<Renderable>(entity, Renderable(Vertices(3), Indices(3)));
			item.Indices = {
				0, 1, 2
			};

			item.Vertices = {
				{Position(-0.5, -0.5), Color(1, 0, 0)},
				{Position(0.0, +0.5), Color(0, 1, 0)},
				{Position(+0.5, -0.5), Color(0, 0, 1)},
			};

			Renderable::Create(item);
		}

		{
			const auto entity = GetEntityManager().create();
			auto& item = GetEntityManager().emplace<Renderable>(entity, Renderable(Vertices(3), Indices(3)));
			item.Indices = {
				0, 1, 2
			};

			item.Vertices = {
				{Position(+0.5, +0.5), Color(1, 0, 0)},
				{Position(0.0, -0.5), Color(0, 1, 0)},
				{Position(-0.5, +0.5), Color(0, 0, 1)},
			};

			Renderable::Create(item);
		}
	}

	void Event(EventType* event) override
	{
		if (Input::IsKeyPressed(Key::Escape))
			Close();

		const auto key_event = reinterpret_cast<KeyEvent*>(event);
		if (*event == EventType::Key)
		{
			if (key_event->key == Key::F11 && key_event->action == Action::Press)
				GetWindow().SetFullscreen(!GetWindow().IsFullscreen());
		}
	}

	void Update() override
	{
		auto view = GetEntityManager().view<Renderable>();

		view.each([this](auto& render)
		{
			for (int i = 0; i < render.Vertices.size(); i++)
				render.Vertices[i].color.a = this->state ? 0.5 : 1;
		});
	}

	void ImGui() override
	{
		if (ImGui::Button("Change"))
			state = !state;

		ImGui::ColorPicker4("Background Color", GetClearColor());
	}

	void Render() override
	{
		auto view = GetEntityManager().view<Renderable>();
		for (auto entity : view)
		{
			auto& item = view.get<Renderable>(entity);
			Renderable::Draw(item);
		}
	}

	void Shutdown() override
	{
	}
};


CREATE_APPLICATION(App)
