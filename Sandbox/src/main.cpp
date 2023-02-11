#include <string>
#include <numeric>
#include <entt/entt.hpp>
#include <glm/glm.hpp>

#include "Engine.h"

using namespace __XXECS;

struct PosColorVertex
{
	float x;
	float y;
	uint32_t abgr;
};

static PosColorVertex cubeVertices[] =
{
	{-1.0f, -1.0f, 0xff0000ff},
	{1.0f, -1.0f, 0xff0000ff},
	{-1.0f, 1.0f, 0xff0000ff},
	{1.0f, 1.0f, 0xff0000ff},
};

static const uint16_t cubeTriList[] =
{
	0, 1, 2,
	1, 3, 2,
};

class App final : public Application
{
public:
	App() = default;

	~App() override = default;

	void Init() override
	{
		Color<float>& color = GetClearColor();
		color.r = 0.5f;
		color.g = 0.5f;
		color.b = 0.5f;
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
		ImGui::ColorPicker4("Background Color", GetClearColor());

		Diligent::DrawAttribs drawAttrs;
		drawAttrs.NumVertices = 3;
		GetImmediateContext().GetNative()->Draw(drawAttrs);

	}

	void Shutdown() override
	{
	}
};


CREATE_APPLICATION(App)
