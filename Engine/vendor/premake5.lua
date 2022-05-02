local BGFX_DIR = "bgfx"
local BIMG_DIR = "bimg"
local BX_DIR = "bx"
local GLFW_DIR = "glfw"
local IMGUI_DIR = "imgui"

function setBxCompat()
	filter "action:vs*"
		includedirs { path.join(BX_DIR, "include/compat/msvc") }
	filter { "system:windows", "action:gmake" }
		includedirs { path.join(BX_DIR, "include/compat/mingw") }
	filter { "system:macosx" }
		includedirs { path.join(BX_DIR, "include/compat/osx") }
		buildoptions { "-x objective-c++" }
end

project "bgfx"
    kind "StaticLib"
    language "C++"
    cppdialect "C++14"
    exceptionhandling "Off"
    rtti "Off"
    defines "__STDC_FORMAT_MACROS"
    files
    {
        path.join(BGFX_DIR, "include/bgfx/**.h"),
        path.join(BGFX_DIR, "src/*.cpp"),
        path.join(BGFX_DIR, "src/*.h"),
    }
    excludes
    {
        path.join(BGFX_DIR, "src/amalgamated.cpp"),
    }
    includedirs
    {
        path.join(BX_DIR, "include"),
        path.join(BIMG_DIR, "include"),
        path.join(BGFX_DIR, "include"),
        path.join(BGFX_DIR, "3rdparty"),
        path.join(BGFX_DIR, "3rdparty/dxsdk/include"),
        path.join(BGFX_DIR, "3rdparty/khronos")
    }
    filter "action:vs*"
        defines "_CRT_SECURE_NO_WARNINGS"
        excludes
        {
            path.join(BGFX_DIR, "src/glcontext_glx.cpp"),
            path.join(BGFX_DIR, "src/glcontext_egl.cpp")
        }
    filter "system:macosx"
        files
        {
            path.join(BGFX_DIR, "src/*.mm"),
        }
    setBxCompat()

project "bimg"
    kind "StaticLib"
    language "C++"
    cppdialect "C++14"
    exceptionhandling "Off"
    rtti "Off"
    files
    {
        path.join(BIMG_DIR, "include/bimg/*.h"),
        path.join(BIMG_DIR, "src/image.cpp"),
        path.join(BIMG_DIR, "src/image_gnf.cpp"),
        path.join(BIMG_DIR, "src/*.h"),
        path.join(BIMG_DIR, "3rdparty/astc-codec/src/decoder/*.cc")
    }
    includedirs
    {
        path.join(BX_DIR, "include"),
        path.join(BIMG_DIR, "include"),
        path.join(BIMG_DIR, "3rdparty/astc-codec"),
        path.join(BIMG_DIR, "3rdparty/astc-codec/include"),
    }
    setBxCompat()

project "bx"
    kind "StaticLib"
    language "C++"
    cppdialect "C++14"
    exceptionhandling "Off"
    rtti "Off"
    defines "__STDC_FORMAT_MACROS"
    files
    {
        path.join(BX_DIR, "include/bx/*.h"),
        path.join(BX_DIR, "include/bx/inline/*.inl"),
        path.join(BX_DIR, "src/*.cpp")
    }
    excludes
    {
        path.join(BX_DIR, "src/amalgamated.cpp"),
        path.join(BX_DIR, "src/crtnone.cpp")
    }
    includedirs
    {
        path.join(BX_DIR, "3rdparty"),
        path.join(BX_DIR, "include"),
        "fixAlloca",
    }
    filter "action:vs*"
        defines "_CRT_SECURE_NO_WARNINGS"
    setBxCompat()
        
project "glfw"
    kind "StaticLib"
    language "C"
    files
    {
        path.join(GLFW_DIR, "include/GLFW/*.h"),
        path.join(GLFW_DIR, "src/platform.h"),
        path.join(GLFW_DIR, "src/platform.c"),
        path.join(GLFW_DIR, "src/mappings.h"),
        path.join(GLFW_DIR, "src/context.c"),
        path.join(GLFW_DIR, "src/egl_context.*"),
        path.join(GLFW_DIR, "src/init.c"),
        path.join(GLFW_DIR, "src/input.c"),
        path.join(GLFW_DIR, "src/internal.h"),
        path.join(GLFW_DIR, "src/monitor.c"),
        path.join(GLFW_DIR, "src/osmesa_context.*"),
        path.join(GLFW_DIR, "src/vulkan.c"),
        path.join(GLFW_DIR, "src/window.c"),

        path.join(GLFW_DIR,"src/null_platform.h"),
        path.join(GLFW_DIR,"src/null_joystick.h"),
        path.join(GLFW_DIR,"src/null_init.c"),

        path.join(GLFW_DIR,"src/null_monitor.c"),
        path.join(GLFW_DIR,"src/null_window.c"),
        path.join(GLFW_DIR,"src/null_joystick.c"),
    }
    includedirs { path.join(GLFW_DIR, "include") }
    filter "system:windows"
        defines "_GLFW_WIN32"
        files
        {
            path.join(GLFW_DIR, "src/win32_*.*"),
            path.join(GLFW_DIR, "src/wgl_context.*")
        }
    filter "system:linux"
        defines "_GLFW_X11"
        files
        {
            path.join(GLFW_DIR, "src/glx_context.*"),
            path.join(GLFW_DIR, "src/linux*.*"),
            path.join(GLFW_DIR, "src/posix*.*"),
            path.join(GLFW_DIR, "src/x11*.*"),
            path.join(GLFW_DIR, "src/xkb*.*")
        }
    filter "system:macosx"
        defines "_GLFW_COCOA"
        files
        {
            path.join(GLFW_DIR, "src/cocoa_*.*"),
            path.join(GLFW_DIR, "src/posix_thread.h"),
            path.join(GLFW_DIR, "src/nsgl_context.h"),
            path.join(GLFW_DIR, "src/egl_context.h"),
            path.join(GLFW_DIR, "src/osmesa_context.h"),

            path.join(GLFW_DIR, "src/posix_thread.c"),
            path.join(GLFW_DIR, "src/nsgl_context.m"),
            path.join(GLFW_DIR, "src/egl_context.c"),
            path.join(GLFW_DIR, "src/nsgl_context.m"),
            path.join(GLFW_DIR, "src/osmesa_context.c"),                       
        }

    filter "action:vs*"
        defines "_CRT_SECURE_NO_WARNINGS"

project "imgui"
    kind "StaticLib"
    language "C++"

    files
    {
         path.join(IMGUI_DIR, "imconfig.h"),
         path.join(IMGUI_DIR, "imgui.h"),
         path.join(IMGUI_DIR, "imgui.cpp"),
         path.join(IMGUI_DIR, "imgui_draw.cpp"),
         path.join(IMGUI_DIR, "imgui_internal.h"),
         path.join(IMGUI_DIR, "imgui_widgets.cpp"),
         path.join(IMGUI_DIR, "imstb_rectpack.h"),
         path.join(IMGUI_DIR, "imstb_textedit.h"),
         path.join(IMGUI_DIR, "imstb_truetype.h"),
         path.join(IMGUI_DIR, "imgui_demo.cpp"),
         path.join(IMGUI_DIR, "imgui_tables.cpp"),

         path.join(IMGUI_DIR, "backends/imgui_impl_glfw.cpp"),
         path.join(IMGUI_DIR, "backends/imgui_impl_glfw.h"),
    }

    includedirs
    {
        IMGUI_DIR,
        path.join(GLFW_DIR, "include"),
    }

    links
    { 
        "glfw"
    }

    filter "action:vs*"
        defines "_CRT_SECURE_NO_WARNINGS"