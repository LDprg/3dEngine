#include <Engine.h>

using namespace __XXECS;

class App : public Application
{
public:
	App() = default;
	~App() override = default;

	void Event(EventType* event) override
	{
		if (Input::IsKeyPressed(Key::Escape))
		{
			Get().Close();
		}
	}

	void Update() override
	{
		ImGui::Text("Hello, world %d", 123);
		ImGui::Button("Save");
	}
};


CREATE_APPLICATION(App)
