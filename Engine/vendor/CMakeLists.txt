cmake_minimum_required(VERSION 3.10)
project(imgui_cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_subdirectory("glfw")

file(GLOB SRC "imgui/*.cpp" "imgui/*.h" "imgui/*.hpp" "imgui/backends/imgui_impl_glfw.h" "imgui/backends/imgui_impl_glfw.cpp")
add_library(imgui_cmake ${SRC})

target_include_directories(imgui_cmake PUBLIC "imgui")

target_link_libraries(imgui_cmake glfw)