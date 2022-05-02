#include <Engine.h>
#include <fstream>

//#include "Engine/Renderer/brtshaderc/brtshaderc.h"

#include "bx/math.h"

using namespace __XXECS;

struct PosColorVertex
{
	float m_x;
	float m_y;
	float m_z;
	uint32_t m_abgr;

	static void init()
	{
		ms_decl
			.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
			.end();
	};

	static bgfx::VertexLayout ms_decl;
};

bgfx::VertexLayout PosColorVertex::ms_decl;

static PosColorVertex s_cubeVertices[] =
{
 {  0.5f,  0.5f, 0.0f, 0xff0000ff },
 {  0.5f, -0.5f, 0.0f, 0xff0000ff },
 { -0.5f, -0.5f, 0.0f, 0xff00ff00 },
 { -0.5f,  0.5f, 0.0f, 0xff00ff00 }
};


static const uint16_t s_cubeTriList[] =
{
 0,1,3,
 1,2,3
};

class App : public Application
{
private:
	bgfx::VertexBufferHandle m_vbh;
	bgfx::IndexBufferHandle m_ibh;
	bgfx::ProgramHandle m_program;
public:
	App()
	{
	}

	~App() override
	{
	}

	void Init() override
	{
		PosColorVertex::init();
		m_vbh = bgfx::createVertexBuffer(
			// Static data can be passed with bgfx::makeRef
			bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices)),
			PosColorVertex::ms_decl
		);

		m_ibh = bgfx::createIndexBuffer(
			// Static data can be passed with bgfx::makeRef
			bgfx::makeRef(s_cubeTriList, sizeof(s_cubeTriList))
		);

		
		// compile vertex shader, with default arguments.
		const bgfx::Memory* memVsh = shaderc::compileShader(shaderc::ST_VERTEX, "v_simple.sc");
		bgfx::ShaderHandle vsh = bgfx::createShader(memVsh);

		// compile fragment shader, with specific arguments for defines, varying def file, shader profile.
		const bgfx::Memory* memFsh = shaderc::compileShader(shaderc::ST_FRAGMENT, "f_simple.sc");
		bgfx::ShaderHandle fsh = bgfx::createShader(memFsh);

		// build program using shaders
		m_program = bgfx::createProgram(vsh, fsh, true);
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

		float mtx[16];
		bx::mtxRotateY(mtx, 0.0f);

		// position x,y,z
		mtx[12] = 0.0f;
		mtx[13] = 0.0f;
		mtx[14] = 0.0f;

		// Set model matrix for rendering.
		bgfx::setTransform(mtx);

		// Set vertex and index buffer.
		bgfx::setVertexBuffer(0, m_vbh);
		bgfx::setIndexBuffer(m_ibh);

		// Set render states.
		bgfx::setState(BGFX_STATE_DEFAULT);

		// Submit primitive for rendering to view 0.
		bgfx::submit(0, m_program);
	}

	void Shutdown() override
	{
		
	}
};


CREATE_APPLICATION(App)
