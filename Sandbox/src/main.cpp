#include <entt/entt.hpp>
#include <glm/ext.hpp>
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

	}

	void Event(EventType* event) override
	{
		if (Input::IsKeyPressed(Key::Escape))
			Get().Close();

		const auto key_event = reinterpret_cast<KeyEvent*>(event);
		if (*event == EventType::Key)
		{
			if (key_event->key == Key::F11 && key_event->action == Action::Press)
				GetWindow().SetFullscreen(!GetWindow().IsFullscreen());
		}
	}

	void UpdateImGui() override
	{
		static bool state;
		if (ImGui::Button("TEST"))
			state = !state;

		if(state)
			ImGui::Text("TEST");
	}

	void Update() override
	{

		
	}

	void Shutdown() override
	{
		
	}
};


CREATE_APPLICATION(App)
