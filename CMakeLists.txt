cmake_minimum_required(VERSION 3.23)
project(Sandbox)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_subdirectory("Engine")

file(GLOB SRC "Sandbox/src/**.c" "Sandbox/src/**.cc" "Sandbox/src/**.cpp" "Sandbox/src/**.h" "Sandbox/src/**.hpp" "Sandbox/src/**.sc" )
add_executable(Sandbox ${SRC})

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