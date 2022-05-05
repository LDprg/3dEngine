#include <Engine.h>

#include <stdio.h>

#include <bx/math.h>
#include <bx/timer.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

using namespace __XXECS;

struct PosColorVertex
{
	float x;
	float y;
	uint32_t abgr;
};

static PosColorVertex cubeVertices[] =
{
	{-1.0f,  -1.0f, 0xff0000ff },
	{ 1.0f,  -1.0f, 0xff0000ff },
	{-1.0f, 1.0f, 0xff0000ff },
	{ 1.0f, 1.0f, 0xff0000ff },
};

static const uint16_t cubeTriList[] =
{
	0, 1, 2,
	1, 3, 2,
};

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
		m_vsh = Renderer::loadShader("v_simple.bin");
		m_fsh = Renderer::loadShader("f_simple.bin");
		m_program = bgfx::createProgram(m_vsh, m_fsh, true);
	}

	void Event(EventType* event) override
	{
		if (Input::IsKeyPressed(Key::Escape))
		{
			Get().Close();
		}

		if (*event == EventType::Key)
		{
			auto keyEvent = (KeyEvent*)event;
			if(keyEvent->key == Key::F11 && keyEvent->action == Action::Press)
				GetWindow().setFullscreen(!GetWindow().isFullscreen());
		}
	}

	void UpdateImGui() override
	{
	}

	void Update() override
	{
		counter++;
		
		glm::mat4 model_matrix(1.0f);
		model_matrix = glm::rotate(model_matrix, counter * 0.01f, glm::vec3(0.0f, 0.0f, 1.0f));
		bgfx::setTransform(glm::value_ptr(model_matrix));

		const bx::Vec3 at = { 0.0f, 0.0f,  0.0f };
		const bx::Vec3 eye = { 0.0f, 0.0f, -3.3f };
		float view[16];
		bx::mtxLookAt(view, eye, at);
		float proj[16];
		bx::mtxProj(proj, 50.0f, float(GetWindow().GetWidth()) / float(GetWindow().GetHeight()), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
		bgfx::setViewTransform(GetRenderer().getView(), view, proj);

		bgfx::setVertexBuffer(0, m_vbh);
		bgfx::setIndexBuffer(m_ibh);

		bgfx::submit(GetRenderer().getView(), m_program);
	}

	void Shutdown() override
	{
		bgfx::destroy(m_ibh);
		bgfx::destroy(m_vbh);
		bgfx::destroy(m_program);
	}
};


CREATE_APPLICATION(App)