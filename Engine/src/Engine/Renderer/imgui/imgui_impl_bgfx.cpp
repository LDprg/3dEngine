#include "pch.hpp"
// Derived from this Gist by Richard Gale:
//     https://gist.github.com/RichardGale/6e2b74bc42b3005e08397236e4be0fd0

// ImGui BFFX binding
// In this binding, ImTextureID is used to store an OpenGL 'GLuint' texture
// identifier. Read the FAQ about ImTextureID in imgui.cpp.

// You can copy and use unmodified imgui_impl_* files in your project. See
// main.cpp for an example of using this. If you use this binding you'll need to
// call 4 functions: ImGui_ImplXXXX_Init(), ImGui_ImplXXXX_NewFrame(),
// ImGui::Render() and ImGui_ImplXXXX_Shutdown(). If you are new to ImGui, see
// examples/README.txt and documentation at the top of imgui.cpp.
// https://github.com/ocornut/imgui

#include "imgui_impl_bgfx.h"
#include "imgui.h"

// BGFX/BX
#include "bgfx/bgfx.h"
#include "bgfx/embedded_shader.h"
#include "bx/math.h"

// Data
static uint8_t g_View = 255;
static bgfx::TextureHandle g_FontTexture = BGFX_INVALID_HANDLE;
static bgfx::ProgramHandle g_ShaderHandle = BGFX_INVALID_HANDLE;
static bgfx::UniformHandle g_AttribLocationTex = BGFX_INVALID_HANDLE;
static bgfx::VertexLayout g_VertexLayout;

// This is the main rendering function that you have to implement and call after
// ImGui::Render(). Pass ImGui::GetDrawData() to this function.
// Note: If text or lines are blurry when integrating ImGui into your engine,
// in your Render function, try translating your projection matrix by
// (0.5f,0.5f) or (0.375f,0.375f)
void ImGui_Implbgfx_RenderDrawLists(ImDrawData* draw_data)
{
	// Avoid rendering when minimized, scale coordinates for retina displays
	// (screen coordinates != framebuffer coordinates)
	const ImGuiIO& io = ImGui::GetIO();
	const int fb_width = static_cast<int>(io.DisplaySize.x * io.DisplayFramebufferScale.x);
	const int fb_height = static_cast<int>(io.DisplaySize.y * io.DisplayFramebufferScale.y);
	if (fb_width == 0 || fb_height == 0)
		return;

	draw_data->ScaleClipRects(io.DisplayFramebufferScale);

	// Setup render state: alpha-blending enabled, no face culling,
	// no depth testing, scissor enabled
	const uint64_t state =
		BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_MSAA |
		BGFX_STATE_BLEND_FUNC(
			BGFX_STATE_BLEND_SRC_ALPHA, BGFX_STATE_BLEND_INV_SRC_ALPHA);

	const bgfx::Caps* caps = bgfx::getCaps();

	// Setup viewport, orthographic projection matrix
	float ortho[16];
	bx::mtxOrtho(
		ortho, 0.0f, io.DisplaySize.x, io.DisplaySize.y, 0.0f, 0.0f, 1000.0f,
		0.0f, caps->homogeneousDepth);
	bgfx::setViewTransform(g_View, nullptr, ortho);
	bgfx::setViewRect(g_View, 0, 0, static_cast<uint16_t>(fb_width), static_cast<uint16_t>(fb_height));

	// Render command lists
	for (int n = 0; n < draw_data->CmdListsCount; n++)
	{
		const ImDrawList* cmd_list = draw_data->CmdLists[n];
		uint32_t idx_buffer_offset = 0;

		bgfx::TransientVertexBuffer tvb;
		bgfx::TransientIndexBuffer tib;

		const uint32_t numVertices = static_cast<uint32_t>(cmd_list->VtxBuffer.size());
		const uint32_t numIndices = static_cast<uint32_t>(cmd_list->IdxBuffer.size());

		if ((numVertices != getAvailTransientVertexBuffer(
				numVertices, g_VertexLayout)) ||
			(numIndices != bgfx::getAvailTransientIndexBuffer(numIndices)))
		{
			// not enough space in transient buffer, quit drawing the rest...
			break;
		}

		allocTransientVertexBuffer(&tvb, numVertices, g_VertexLayout);
		allocTransientIndexBuffer(&tib, numIndices);

		auto verts = (ImDrawVert*)tvb.data;
		memcpy(
			verts, cmd_list->VtxBuffer.begin(),
			numVertices * sizeof(ImDrawVert));

		auto indices = (ImDrawIdx*)tib.data;
		memcpy(
			indices, cmd_list->IdxBuffer.begin(),
			numIndices * sizeof(ImDrawIdx));

		for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++)
		{
			const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];

			if (pcmd->UserCallback)
				pcmd->UserCallback(cmd_list, pcmd);
			else
			{
				const uint16_t xx = static_cast<uint16_t>(bx::max(pcmd->ClipRect.x, 0.0f));
				const uint16_t yy = static_cast<uint16_t>(bx::max(pcmd->ClipRect.y, 0.0f));
				bgfx::setScissor(
					xx, yy, static_cast<uint16_t>(bx::min(pcmd->ClipRect.z, 65535.0f)) - xx,
					static_cast<uint16_t>(bx::min(pcmd->ClipRect.w, 65535.0f)) - yy);

				bgfx::setState(state);
				const bgfx::TextureHandle texture = {
					static_cast<uint16_t>((intptr_t)pcmd->TextureId & 0xffff)
				};
				setTexture(0, g_AttribLocationTex, texture);
				setVertexBuffer(0, &tvb, 0, numVertices);
				setIndexBuffer(&tib, idx_buffer_offset, pcmd->ElemCount);
				submit(g_View, g_ShaderHandle);
			}

			idx_buffer_offset += pcmd->ElemCount;
		}
	}
}

bool ImGui_Implbgfx_CreateFontsTexture()
{
	// Build texture atlas
	const ImGuiIO& io = ImGui::GetIO();
	unsigned char* pixels;
	int width, height;
	io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

	// Upload texture to graphics system
	g_FontTexture = createTexture2D(
		static_cast<uint16_t>(width), static_cast<uint16_t>(height), false, 1, bgfx::TextureFormat::BGRA8,
		0, bgfx::copy(pixels, width * height * 4));

	// Store our identifier
	io.Fonts->TexID = (void*)static_cast<intptr_t>(g_FontTexture.idx);

	return true;
}

#include "fs_ocornut_imgui.bin.h"
#include "vs_ocornut_imgui.bin.h"

static const bgfx::EmbeddedShader s_embeddedShaders[] = {
	BGFX_EMBEDDED_SHADER(vs_ocornut_imgui),
	BGFX_EMBEDDED_SHADER(fs_ocornut_imgui), BGFX_EMBEDDED_SHADER_END()
};

bool ImGui_Implbgfx_CreateDeviceObjects()
{
	const bgfx::RendererType::Enum type = bgfx::getRendererType();
	g_ShaderHandle = createProgram(
		createEmbeddedShader(s_embeddedShaders, type, "vs_ocornut_imgui"),
		createEmbeddedShader(s_embeddedShaders, type, "fs_ocornut_imgui"),
		true);

	g_VertexLayout.begin()
	              .add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
	              .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
	              .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
	              .end();

	g_AttribLocationTex =
		createUniform("g_AttribLocationTex", bgfx::UniformType::Sampler);

	ImGui_Implbgfx_CreateFontsTexture();

	return true;
}

void ImGui_Implbgfx_InvalidateDeviceObjects()
{
	destroy(g_AttribLocationTex);
	destroy(g_ShaderHandle);

	if (isValid(g_FontTexture))
	{
		destroy(g_FontTexture);
		ImGui::GetIO().Fonts->TexID = nullptr;
		g_FontTexture.idx = bgfx::kInvalidHandle;
	}
}

void ImGui_Implbgfx_Init(int view)
{
	g_View = static_cast<uint8_t>(view & 0xff);
}

void ImGui_Implbgfx_Shutdown()
{
	ImGui_Implbgfx_InvalidateDeviceObjects();
}

void ImGui_Implbgfx_NewFrame()
{
	if (!isValid(g_FontTexture))
		ImGui_Implbgfx_CreateDeviceObjects();
}
