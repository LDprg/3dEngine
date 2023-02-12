#include "imgui.h"

void __XXECS::ImguiManager::Init()
{
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGuiIO& io = ImGui::GetIO();
	io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
	io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

	io.KeyMap[ImGuiKey_Tab] = static_cast<int>(Key::Tab);
	io.KeyMap[ImGuiKey_LeftArrow] = static_cast<int>(Key::Left);
	io.KeyMap[ImGuiKey_RightArrow] = static_cast<int>(Key::Right);
	io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
	io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
	io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
	io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
	io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
	io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
	io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
	io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
	io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
	io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
	io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
	io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
	io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
	io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
	io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
	io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
	io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
	io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

	m_pImgui = std::make_unique<Diligent::ImGuiDiligentRenderer>(Application::Get().GetDevice().GetNative(),
	                                                             Application::Get().GetSwapChain().GetDesc().
	                                                             ColorBufferFormat,
	                                                             Application::Get().GetSwapChain().GetDesc().
	                                                             DepthBufferFormat,
	                                                             Application::Get().GetSwapChain().GetDesc().
	                                                             BufferCount,
	                                                             Application::Get().GetSwapChain().GetDesc().
	                                                             BufferCount);
	m_pImgui->CreateFontsTexture();
}

void __XXECS::ImguiManager::Event(EventType* event) const
{
	ImGuiIO& io = ImGui::GetIO();

	if (*event == EventType::Resize)
	{
		const auto resizeEvent = reinterpret_cast<ResizeEvent*>(event);

		Application::Get().GetSwapChain().GetNative()->Resize(resizeEvent->width, resizeEvent->height);
	}

	if (*event == EventType::Key)
	{
		const auto key_event = reinterpret_cast<KeyEvent*>(event);
		if (key_event->action == Action::Press)
		{
			io.MouseDown[static_cast<int>(key_event->key)] = true;
			io.KeysDown[static_cast<int>(key_event->key)] = true;
		}
		if (key_event->action == Action::Release)
		{
			io.MouseDown[static_cast<int>(key_event->key)] = false;
			io.KeysDown[static_cast<int>(key_event->key)] = false;
		}
	}

	if (*event == EventType::MouseMoved)
	{
		const auto moved_event = reinterpret_cast<MouseMovedEvent*>(event);
		io.MousePos = ImVec2(static_cast<float>(moved_event->x), static_cast<float>(moved_event->y));
	}
}

void __XXECS::ImguiManager::NewFrame()
{
	const auto& SCDesc = Application::Get().GetSwapChain().GetDesc();
	m_pImgui->NewFrame(SCDesc.Width, SCDesc.Height, SCDesc.PreTransform);

	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = ImVec2(static_cast<float>(SCDesc.Width), static_cast<float>(SCDesc.Height));

	ImGui::NewFrame();
}

void __XXECS::ImguiManager::Render()
{
	ImGui::Render();
	m_pImgui->RenderDrawData(Application::Get().GetImmediateContext().GetNative(), ImGui::GetDrawData());
}

void __XXECS::ImguiManager::Destory()
{
	m_pImgui->InvalidateDeviceObjects();
	m_pImgui.release();
	ImGui::DestroyContext();
}
