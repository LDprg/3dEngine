local BUILD_DIR = path.join("build", _ACTION)
if _OPTIONS["cc"] ~= nil then
	BUILD_DIR = BUILD_DIR .. "_" .. _OPTIONS["cc"]
end

IncludeDir = {}
IncludeDir["bgfx"] = "Engine/vendor/bgfx/include"
IncludeDir["bx"] = "Engine/vendor/bx/include"
IncludeDir["bimg"] = "Engine/vendor/bimg/include"
IncludeDir["glfw"] = "Engine/vendor/glfw/include"
IncludeDir["spdlog"] = "Engine/vendor/spdlog/include"
IncludeDir["entt"] = "Engine/vendor/entt/single_include/entt"
IncludeDir["imgui"] = "Engine/vendor/imgui"

workspace "Engine"
	location(BUILD_DIR)
	startproject "Sandbox"

	configurations { "Release", "Debug" }
	if os.is64bit() and not os.istarget("windows") then
		platforms "x86_64"
	else
		platforms { "x86", "x86_64" }
	end
	filter "configurations:Release"
		defines "NDEBUG"
		optimize "Full"
	filter "configurations:Debug*"
		defines "_DEBUG"
		optimize "Debug"
		symbols "On"
	filter "platforms:x86"
		architecture "x86"
	filter "platforms:x86_64"
		architecture "x86_64"
	filter "system:macosx"
		xcodebuildsettings {
			["MACOSX_DEPLOYMENT_TARGET"] = "10.9",
			["ALWAYS_SEARCH_USER_PATHS"] = "YES", -- This is the minimum version of macos we'll be able to run on
		};
	filter "configurations:Debug"
        defines "BX_CONFIG_DEBUG=1"
	filter "configurations:Release"
		defines "BX_CONFIG_DEBUG=0"

include "Engine/vendor"

project "Engine"
	kind "StaticLib"
	language "C++"	
	cppdialect "C++20"
	staticruntime "off"

	pchheader "pch.hpp"
	pchsource "%{prj.name}/src/pch.cpp"

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp",
	}

	includedirs{
		"%{prj.name}/src",
		"%{IncludeDir.bgfx}",
		"%{IncludeDir.bx}",
		"%{IncludeDir.bimg}",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.imgui}"
	}

	links { 
		"bgfx", 
		"bimg", 
		"bx", 
		"glfw",
		"imgui",
	}

	filter "system:windows"
		links { "psapi" }
	filter "system:linux"
		links { "dl", "GL", "pthread", "X11" }
	filter "system:macosx"
		links { "QuartzCore.framework", "Metal.framework", "Cocoa.framework", "IOKit.framework", "CoreVideo.framework" }
	setBxCompat()
	
project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"

	files{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.cpp"
	}

	includedirs{
		"Engine/src",
		"%{IncludeDir.bgfx}",
		"%{IncludeDir.bgfx_ext}",
		"%{IncludeDir.bx}",
		"%{IncludeDir.bimg}",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.imgui}"
	}

	links{
		"Engine"
	}