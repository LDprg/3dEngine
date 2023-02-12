#include <numeric>
#include <string>
#include <Engine/Entity/Components/RenderableComp.hpp>
#include <entt/entt.hpp>
#include <glm/glm.hpp>
#include <Graphics/GraphicsTools/interface/MapHelper.hpp>

#include "Engine.h"

using namespace __XXECS;

class App final : public Application
{
protected:
	Renderable m_Renderable;

public:
	App() : Application(), m_Renderable(Vertices{
		                                    {Position(-0.5, -0.5), Color(1, 0, 0)},
		                                    {Position(0.0, +0.5), Color(0, 1, 0)},
		                                    {Position(+0.5, -0.5), Color(0, 0, 1)},
	                                    }, Indices{
		                                    0, 1, 2
	                                    })
	{
	}

	~App() override = default;

	void Init() override
	{
		GetClearColor() = {0.5f, 0.5f, 0.5f};

		/*m_Renderable.Indices = {
			0, 1, 2
		};

		m_Renderable.Vertices = {
			{Position(-0.5, -0.5), Color(1, 0, 0)},
			{Position(0.0, +0.5),  Color(0, 1, 0)},
			{Position(+0.5, -0.5), Color(0, 0, 1)},
		};*/

		m_Renderable.Create();
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
	}

	void ImGui() override
	{
		static bool state = false;

		if (state)
			m_Renderable.Vertices[0].color.a = 0;
		else
			m_Renderable.Vertices[0].color.a = 1;

		if (ImGui::Button("Change"))
			state = !state;

		ImGui::ColorPicker4("Background Color", GetClearColor());
	}

	void Render() override
	{
		m_Renderable.Draw();
	}

	void Shutdown() override
	{
	}
};


CREATE_APPLICATION(App)
