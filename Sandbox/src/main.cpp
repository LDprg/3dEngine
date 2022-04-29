#include <Engine.h>

using namespace __XXECS;

class App : public Application
{
public:
	App() {}
	~App() {}

	void Event(EventType* event)
	{
		if (Input::IsKeyPressed(KEY_ESCAPE))
		{
			Application::Get().Close();
		}
		
		if (*event == EventType::Exit)
		{
			Application::Get().Close();
		}
	}

	void Update()
	{
		
	}
};



CREATE_APPLICATION(App)