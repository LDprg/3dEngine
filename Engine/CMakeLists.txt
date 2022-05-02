cmake_minimum_required(VERSION 3.10)
project(Engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_subdirectory("vendor/bgfx.cmake")
add_subdirectory("vendor/entt")
#add_subdirectory("vendor/glfw")
add_subdirectory("vendor") #imgui
add_subdirectory("vendor/spdlog")


file(GLOB_RECURSE SRC "src/*.cpp" "src/*.h" "src/*.hpp" )
add_library(Engine ${SRC})

target_precompile_headers(Engine PRIVATE "src/pch.hpp")

target_include_directories(Engine PUBLIC "src")
target_include_directories(Engine PUBLIC "vendor/imgui")
target_include_directories(Engine PUBLIC "vendor/entt/single_include")
target_include_directories(Engine PUBLIC "vendor/spdlog/include")
target_include_directories(Engine PUBLIC "vendor/glfw/include")

set(BGFX_BUILD_TOOLS ON CACHE INTERNAL "" FORCE)

target_link_libraries(Engine glfw)
#target_link_libraries(Engine entt)
target_link_libraries(Engine bgfx)
target_link_libraries(Engine bx)
target_link_libraries(Engine bimg)
target_link_libraries(Engine imgui_cmake)

#[[target_link_libraries(Engine astc)
target_link_libraries(Engine astc-codec)
target_link_libraries(Engine edtaa3)
target_link_libraries(Engine etc1)
target_link_libraries(Engine etc2)
target_link_libraries(Engine fcpp)
target_link_libraries(Engine glcpp)
target_link_libraries(Engine glslang)
target_link_libraries(Engine glsl-optimizer)
target_link_libraries(Engine iqa)
target_link_libraries(Engine mesa)
target_link_libraries(Engine meshoptimizer)
target_link_libraries(Engine nvtt)
target_link_libraries(Engine pvrtc)
target_link_libraries(Engine spirv-cross)
target_link_libraries(Engine spirv-tools)
target_link_libraries(Engine squish)
target_link_libraries(Engine tinyexr)]]