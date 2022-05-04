#include <Engine.h>
#include <stdio.h>
#include <bx/math.h>
#include <bx/timer.h>

using namespace __XXECS;

struct PosColorVertex
{
	float x;
	float y;
	uint32_t abgr;
};

static PosColorVertex cubeVertices[] =
{
	{-0.5f,  -0.5f, 0xff0000ff },
	{ 0.5f,  -0.5f, 0xff0000ff },
	{-0.5f, 0.5f, 0xff0000ff },
	{ 0.5f, 0.5f, 0xff0000ff },
};

static const uint16_t cubeTriList[] =
{
	0, 1, 2,
	1, 3, 2,
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
	bgfx::ProgramHandle m_program;

	bgfx::VertexBufferHandle m_vbh;
	bgfx::IndexBufferHandle m_ibh;
	bgfx::VertexLayout m_layout;

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
		m_layout
			.begin()
			.add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
			.end();
		
		m_vbh = bgfx::createVertexBuffer(bgfx::makeRef(cubeVertices, sizeof(cubeVertices)), m_layout);
		m_ibh = bgfx::createIndexBuffer(bgfx::makeRef(cubeTriList, sizeof(cubeTriList)));

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

	void UpdateImGui() override
	{
	}

	void Update() override
	{
		counter++;

		float mtx[16];
		bx::mtxRotateZ(mtx, counter * 0.01f);
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