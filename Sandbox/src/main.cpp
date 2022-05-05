#include <bx/math.h>
#include <entt/entt.hpp>
#include <glm/ext.hpp>
#include <glm/glm.hpp>

#include "Engine.h"

using namespace __XXECS;

struct PosColorVertex
{
	float x;
	float y;
	uint32_t abgr;
};

static PosColorVertex cubeVertices[] =
{
	{-1.0f, -1.0f, 0xff0000ff},
	{1.0f, -1.0f, 0xff0000ff},
	{-1.0f, 1.0f, 0xff0000ff},
	{1.0f, 1.0f, 0xff0000ff},
};

static const uint16_t cubeTriList[] =
{
	0, 1, 2,
	1, 3, 2,
};

class App final : public Application
{
private:
	bgfx::ShaderHandle m_fsh;
	bgfx::ShaderHandle m_vsh;
	bgfx::ProgramHandle m_program;

	bgfx::VertexBufferHandle m_vbh;
	bgfx::IndexBufferHandle m_ibh;
	bgfx::VertexLayout m_layout;

	int m_counter = 0;
public:
	App() = default;

	~App() override = default;

	void Init() override
	{
		// Create vertex stream declaration.
		m_layout
			.begin()
			.add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
			.end();

		m_vbh = createVertexBuffer(bgfx::makeRef(cubeVertices, sizeof(cubeVertices)), m_layout);
		m_ibh = createIndexBuffer(bgfx::makeRef(cubeTriList, sizeof(cubeTriList)));

		// Create program from shader.
		m_vsh = Renderer::LoadShader("v_simple.bin");
		m_fsh = Renderer::LoadShader("f_simple.bin");
		m_program = createProgram(m_vsh, m_fsh, true);
	}

	void Event(EventType* event) override
	{
		if (Input::IsKeyPressed(Key::Escape))
			Get().Close();

		const auto key_event = reinterpret_cast<KeyEvent*>(event);
		if (*event == EventType::Key)
		{
			if (key_event->key == Key::F11 && key_event->action == Action::Press)
				GetWindow().SetFullscreen(!GetWindow().IsFullscreen());
		}
	}

	void UpdateImGui() override
	{
	}

	void Update() override
	{
		m_counter++;

		glm::mat4 model_matrix(1.0f);
		model_matrix = rotate(model_matrix, static_cast<float>(m_counter) * 0.01f, glm::vec3(0.0f, 0.0f, 1.0f));
		bgfx::setTransform(value_ptr(model_matrix));

		const bx::Vec3 at = {0.0f, 0.0f, 0.0f};
		const bx::Vec3 eye = {0.0f, 0.0f, -3.3f};
		float view[16];
		mtxLookAt(view, eye, at);
		float proj[16];
		bx::mtxProj(proj, 50.0f,
		            GetWindow().GetWidth() / GetWindow().GetHeight(), 0.1f,
		            100.0f, bgfx::getCaps()->homogeneousDepth);
		bgfx::setViewTransform(GetRenderer().GetView(), view, proj);

		setVertexBuffer(0, m_vbh);
		setIndexBuffer(m_ibh);

		submit(GetRenderer().GetView(), m_program);
	}

	void Shutdown() override
	{
		destroy(m_ibh);
		destroy(m_vbh);
		destroy(m_program);
	}
};


CREATE_APPLICATION(App)
