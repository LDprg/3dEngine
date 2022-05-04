#include <Engine.h>
#include <stdio.h>
#include <bx/math.h>
#include <bx/timer.h>

using namespace __XXECS;

struct PosColorVertex
{
	float m_x;
	float m_y;
	float m_z;
	uint32_t m_abgr;

	static void init()
	{
		ms_layout
			.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
			.end();
	};

	static bgfx::VertexLayout ms_layout;
};

bgfx::VertexLayout PosColorVertex::ms_layout;

static PosColorVertex s_cubeVertices[] =
{
	{-1.0f,  1.0f,  1.0f, 0xff000000 },
	{ 1.0f,  1.0f,  1.0f, 0xff0000ff },
	{-1.0f, -1.0f,  1.0f, 0xff00ff00 },
	{ 1.0f, -1.0f,  1.0f, 0xff00ffff },
	{-1.0f,  1.0f, -1.0f, 0xffff0000 },
	{ 1.0f,  1.0f, -1.0f, 0xffff00ff },
	{-1.0f, -1.0f, -1.0f, 0xffffff00 },
	{ 1.0f, -1.0f, -1.0f, 0xffffffff },
};

static const uint16_t s_cubeTriList[] =
{
	0, 1, 2, // 0
	1, 3, 2,
	4, 6, 5, // 2
	5, 6, 7,
	0, 2, 4, // 4
	4, 2, 6,
	1, 5, 3, // 6
	5, 7, 3,
	0, 4, 1, // 8
	4, 5, 1,
	2, 3, 6, // 10
	6, 3, 7,
};

bgfx::ShaderHandle loadShader(const char* FILENAME)
{
	const char* shaderPath = "???";

	switch (bgfx::getRendererType())
	{
	case bgfx::RendererType::Noop:
	case bgfx::RendererType::Direct3D9:  shaderPath = "shaders/dx9/";   break;
	case bgfx::RendererType::Direct3D11:
	case bgfx::RendererType::Direct3D12: shaderPath = "shaders/dx11/";  break;
	case bgfx::RendererType::Gnm:        shaderPath = "shaders/pssl/";  break;
	case bgfx::RendererType::Metal:      shaderPath = "shaders/metal/"; break;
	case bgfx::RendererType::OpenGL:     shaderPath = "shaders/glsl/";  break;
	case bgfx::RendererType::OpenGLES:   shaderPath = "shaders/essl/";  break;
	case bgfx::RendererType::Vulkan:     shaderPath = "shaders/spirv/"; break;
	}

	size_t shaderLen = strlen(shaderPath);
	size_t fileLen = strlen(FILENAME);
	char* filePath = (char*)malloc(shaderLen + fileLen);
	memcpy(filePath, shaderPath, shaderLen);
	memcpy(&filePath[shaderLen], FILENAME, fileLen);

	FILE* file = fopen(FILENAME, "rb");
	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	const bgfx::Memory* mem = bgfx::alloc(fileSize + 1);
	fread(mem->data, 1, fileSize, file);
	mem->data[mem->size - 1] = '\0';
	fclose(file);

	return bgfx::createShader(mem);
}


class App : public Application
{
private:
	bgfx::ShaderHandle m_fsh;
	bgfx::ShaderHandle m_vsh;
	bgfx::VertexBufferHandle m_vbh;
	bgfx::IndexBufferHandle m_ibh;
	bgfx::ProgramHandle m_program;
	int counter = 0;
public:
	App()
	{
		
	}

	~App() override
	{
	}

	void Init() override
	{
		
		// Create vertex stream declaration.
		PosColorVertex::init();
		m_vbh = bgfx::createVertexBuffer(bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices)), PosColorVertex::ms_layout);
		m_ibh = bgfx::createIndexBuffer(bgfx::makeRef(s_cubeTriList, sizeof(s_cubeTriList)));

		// Create program from shaders.
		m_vsh = loadShader("v_simple.bin");
		m_fsh = loadShader("f_simple.bin");		
		m_program = bgfx::createProgram(m_vsh, m_fsh, true);
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
		counter++;

		static bool toggle = false;
		ImGui::Begin("nice");

		if (ImGui::Button("Save"))
			toggle = !toggle;
		if(toggle)
			ImGui::Text("Hello, world");

		ImGui::End();
		
		const bx::Vec3 at = { 0.0f, 0.0f,  0.0f };
		const bx::Vec3 eye = { 0.0f, 0.0f, -5.0f };
		float view[16];
		bx::mtxLookAt(view, eye, at);
		float proj[16];
		bx::mtxProj(proj, 60.0f, float(1024) / float(720), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
		bgfx::setViewTransform(0, view, proj);

		float mtx[16];
		bx::mtxRotateXY(mtx, counter * 0.01f, counter * 0.01f);
		bgfx::setTransform(mtx);

		bgfx::setVertexBuffer(0, m_vbh);
		bgfx::setIndexBuffer(m_ibh);

		bgfx::submit(0, m_program);
	}

	void Shutdown() override
	{
		bgfx::destroy(m_ibh);
		bgfx::destroy(m_vbh);
		bgfx::destroy(m_program);
	}
};


CREATE_APPLICATION(App)
