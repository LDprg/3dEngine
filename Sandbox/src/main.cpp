#include <numeric>
#include <string>
#include <entt/entt.hpp>
#include <glm/glm.hpp>
#include <Graphics/GraphicsTools/interface/MapHelper.hpp>

#include "Engine.h"

using namespace __XXECS;

Vertices TriVerts =
{
	{Position<float>(-0.5, -0.5, 0.0), Color<float>(1, 0, 0)},
	{Position<float>(0.0, +0.5, 0.0), Color<float>(0, 1, 0)},
	{Position<float>(+0.5, -0.5, 0.0), Color<float>(0, 0, 1)},
};

const Indices TriIndices =
{
	0, 1, 2
};

class App final : public Application
{
protected:
	Diligent::RefCntAutoPtr<Diligent::IBuffer> m_CubeVertexBuffer;
	Diligent::RefCntAutoPtr<Diligent::IBuffer> m_CubeIndexBuffer;

public:
	App() = default;

	~App() override = default;

	void Init() override
	{
		GetClearColor() = {0.5f, 0.5f, 0.5f, 1.0f};
		
		Diligent::BufferDesc VertBuffDesc;
		VertBuffDesc.Name = "Vertex buffer";
		VertBuffDesc.Usage = Diligent::USAGE_DYNAMIC;
		VertBuffDesc.CPUAccessFlags = Diligent::CPU_ACCESS_WRITE;
		VertBuffDesc.BindFlags = Diligent::BIND_VERTEX_BUFFER;
		VertBuffDesc.Size = TriVerts.getSize();
		GetDevice().GetNative()->CreateBuffer(VertBuffDesc, nullptr, &m_CubeVertexBuffer);

		Diligent::BufferDesc IndBuffDesc;
		IndBuffDesc.Name = "Index buffer";
		IndBuffDesc.Usage = Diligent::USAGE_IMMUTABLE;
		IndBuffDesc.BindFlags = Diligent::BIND_INDEX_BUFFER;
		IndBuffDesc.Size = TriIndices.getSize();
		Diligent::BufferData IBData;
		IBData.pData = TriIndices;
		IBData.DataSize = TriIndices.getSize();
		GetDevice().GetNative()->CreateBuffer(IndBuffDesc, &IBData, &m_CubeIndexBuffer);
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
		Diligent::IBuffer* pBuffs[] = {m_CubeVertexBuffer};
		GetImmediateContext().GetNative()->SetVertexBuffers(0, 1, pBuffs, &offset,
		                                                    Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION,
		                                                    Diligent::SET_VERTEX_BUFFERS_FLAG_RESET);
		GetImmediateContext().GetNative()->SetIndexBuffer(m_CubeIndexBuffer, 0,
		                                                  Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

	}

	void ImGui() override
	{
		Diligent::MapHelper<Vertex<float>> Vertices(GetImmediateContext().GetNative(), m_CubeVertexBuffer, Diligent::MAP_WRITE, Diligent::MAP_FLAG_DISCARD);
		for (Diligent::Uint32 v = 0; v < TriVerts.size; ++v)
		{
			Vertices[v] = TriVerts[v];
		}

		static bool state = false;

		if (state)
			TriVerts[0].color = Color<float>(1, 0, 0, 0);
		else
			TriVerts[0].color = Color<float>(1, 0, 0, 1);

		if (ImGui::Button("Change"))
			state = !state;

		ImGui::ColorPicker4("Background Color", GetClearColor());
	}

	void Render() override
	{
		Diligent::DrawIndexedAttribs drawAttrs;
		drawAttrs.IndexType = Diligent::VT_UINT32;
		drawAttrs.NumIndices = TriVerts.size;
		drawAttrs.Flags = Diligent::DRAW_FLAG_VERIFY_ALL;
		GetImmediateContext().GetNative()->DrawIndexed(drawAttrs);
	}

	void Shutdown() override
	{
	}
};


CREATE_APPLICATION(App)
