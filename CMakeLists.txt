cmake_minimum_required(VERSION 3.23)
project(Sandbox)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_subdirectory("Engine")

file(GLOB_RECURSE SRC "Sandbox/src/**.cpp" "Sandbox/src/**.ixx" )
add_executable(Sandbox ${SRC})

target_link_libraries(Sandbox Engine)

if (MSVC)
  copy_required_dlls(Sandbox)

  set_property( DIRECTORY PROPERTY VS_STARTUP_PROJECT "Sandbox")
endif (MSVC)