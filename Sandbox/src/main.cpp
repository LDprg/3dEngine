#include <Engine.h>

using namespace __XXECS;

class App : public Application
{
public:
	App() {}
	~App() {}

	void Event(EventType* event)
	{
		if (Input::IsKeyPressed(Key::Escape))
		{
			Application::Get().Close();
		}
	}

	void Update()
	{
		ImGui::Text("Hello, world %d", 123);
		ImGui::Button("Save");
	}
};



CREATE_APPLICATION(App)