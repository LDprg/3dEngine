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
	App() = default;

	~App() override = default;

	void Init() override
	{
		GetClearColor() = {0.5f, 0.5f, 0.5f, 1.0f};

		m_Renderable.Indices = {
			0, 1, 2
		};

		m_Renderable.Create();

		m_Renderable.Vertices = {
			{Position<float>(-0.5, -0.5, 0.0), Color<float>(1, 0, 0)},
			{Position<float>(0.0, +0.5, 0.0), Color<float>(0, 1, 0)},
			{Position<float>(+0.5, -0.5, 0.0), Color<float>(0, 0, 1)},
		};
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
		const Diligent::Uint64 offset = 0;
		Diligent::IBuffer* pBuffs[] = {
			m_Renderable.VertexBuffer	
		};
		GetImmediateContext().GetNative()->SetVertexBuffers(0, 1, pBuffs, &offset,
		                                                    Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION,
		                                                    Diligent::SET_VERTEX_BUFFERS_FLAG_RESET);
		GetImmediateContext().GetNative()->SetIndexBuffer(m_Renderable.IndexBuffer, 0,
		                                                  Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

	}

	void ImGui() override
	{
		Diligent::MapHelper<Vertex<float>> Vertices(GetImmediateContext().GetNative(), m_Renderable.VertexBuffer, Diligent::MAP_WRITE, Diligent::MAP_FLAG_DISCARD);
		for (Diligent::Uint32 v = 0; v < m_Renderable.Vertices.size(); ++v)
		{
			Vertices[v] = m_Renderable.Vertices[v];
		}

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
