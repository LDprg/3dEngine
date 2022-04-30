#include <Engine.h>

using namespace __XXECS;

class App : public Application
{
public:
	App(const char* _name, const char* _description, const char* _url)
		:Application(_name, _description, _url)
	{
		
	}

	void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) override
	{
		
	}

	bool update() override
	{
		
	}

	int shutdown() override
	{
		
	}
};


CREATE_APP(App, "application", "simple test app", "https://github.com/LDprg/3dEngine");
