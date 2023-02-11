cmake_minimum_required(VERSION 3.23)
project(Sandbox)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_subdirectory("Engine")
target_include_directories(Engine PUBLIC "Engine/vendor/DiligentEngine/DiligentCore")
target_include_directories(Engine PUBLIC "Engine/vendor/DiligentEngine/DiligentFX")
target_include_directories(Engine PUBLIC "Engine/vendor/DiligentEngine/DiligentTools")

file(GLOB SRC "Sandbox/src/**.c" "Sandbox/src/**.cpp" "Sandbox/src/**.h" "Sandbox/src/**.hpp" )
add_executable(Sandbox ${SRC})
target_compile_options(Sandbox PUBLIC -DUNICODE -DENGINE_DLL)

target_link_libraries(Sandbox Engine)
target_link_libraries(Sandbox
    Diligent-GraphicsEngineD3D11-shared
    Diligent-GraphicsEngineOpenGL-shared
    Diligent-GraphicsEngineD3D12-shared
    Diligent-GraphicsEngineVk-shared

    Diligent-Imgui
)

copy_required_dlls(Sandbox)

if (MSVC)
  set_property( DIRECTORY PROPERTY VS_STARTUP_PROJECT "Sandbox")
endif (MSVC)