#include "pch.hpp"

void __XXECS::Renderer::Init()
{
	bgfx::renderFrame();
}

void __XXECS::Renderer::Exit()
{
	while (bgfx::RenderFrame::NoContext != bgfx::renderFrame()) {}
	m_renderThread.shutdown();
}

void __XXECS::Renderer::Update()
{
	bgfx::renderFrame();
}

void __XXECS::Renderer::Bind(RenderArguments renderArgs)
{
	m_renderArgs = renderArgs;
	m_renderThread.init(runThread, &m_renderArgs);
}

int32_t __XXECS::Renderer::runThread(bx::Thread* self, void* userData)
{
	auto args = (RenderArguments*)userData;
	// Initialize bgfx using the native window handle and window resolution.
	bgfx::Init init;
	init.platformData = args->platformData;
	init.resolution.width = args->width;
	init.resolution.height = args->height;
	init.resolution.reset = BGFX_RESET_VSYNC;
	LOG_CORE_ASSERT(bgfx::init(init), "BGFX INIT FAILED");
	// Set view 0 to the same dimensions as the window and to clear the color buffer.
	const bgfx::ViewId kClearView = 0;
	bgfx::setViewClear(kClearView, BGFX_CLEAR_COLOR);
	bgfx::setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);
	uint32_t width = args->width;
	uint32_t height = args->height;

	while (Application::Get().isRunning())
	{
		// Handle events from the main thread.
		while (auto ev = (EventType*)Application::Get().GetEventManager().pop())
		{
			if (*ev == EventType::Resize)
			{
				auto resizeEvent = (ResizeEvent*)ev;
				bgfx::reset(resizeEvent->width, resizeEvent->height, BGFX_RESET_VSYNC);
				bgfx::setViewRect(kClearView, 0, 0, bgfx::BackbufferRatio::Equal);
				width = resizeEvent->width;
				height = resizeEvent->height;
			}

			Application::Get().Event(ev);

			delete ev;
		}

		bgfx::touch(kClearView);

		Application::Get().Update();
		bgfx::frame();
	}
	bgfx::shutdown();
	return 0;
}
