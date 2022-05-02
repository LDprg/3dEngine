#include <Engine.h>

using namespace __XXECS;

class App : public Application
{
public:
	App()
	{
	}

	~App() override
	{
	}

	void Event(EventType* event) override
	{
		if (Input::IsKeyPressed(Key::Escape))
		{
			Get().Close();
		}
	}

	void Update() override
	{
		static bool toggle = false;
		ImGui::Begin("nice");

		if (ImGui::Button("Save"))
			toggle = !toggle;
		if(toggle)
			ImGui::Text("Hello, world");

		ImGui::End();
	}
};


CREATE_APPLICATION(App)
