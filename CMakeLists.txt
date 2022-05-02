cmake_minimum_required(VERSION 3.23)
project(Sandbox)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_subdirectory("./Engine")

target_link_libraries(Sandbox Engine)

file(GLOB SRC "Sandbox/src/**.c" "Sandbox/src/**.cc" "Sandbox/src/**.cpp" "Sandbox/src/**.h" "Sandbox/src/**.hpp" )
add_executable(Sandbox ${SRC})

if (MSVC)
  set_property( DIRECTORY PROPERTY VS_STARTUP_PROJECT "LibTorchTemplate")
endif (MSVC)