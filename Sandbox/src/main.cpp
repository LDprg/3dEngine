#include <Engine.h>
#include <fstream>

using namespace __XXECS;

bgfx::ShaderHandle loadShader(const std::string& shader_path)
{
	std::ifstream input_stream(shader_path, std::ios::binary);
	if (!input_stream.is_open())
	{
		throw std::runtime_error("Failed to open a shader file.");
	}

	input_stream.seekg(0, std::ios::end);
	const long file_size = input_stream.tellg();
	input_stream.seekg(0);
	const bgfx::Memory* mem = bgfx::alloc(file_size + 1);
	input_stream.read(reinterpret_cast<char*>(mem->data), file_size);
	mem->data[mem->size - 1] = '\0';

	return bgfx::createShader(mem);
}

class App : public Application
{
public:
	App()
	{
	}

	~App() override
	{
	}

	void Init() override
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

	void Shutdown() override
	{
		
	}
};


CREATE_APPLICATION(App)
