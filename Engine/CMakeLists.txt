cmake_minimum_required(VERSION 3.10)
project(Engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)


add_subdirectory("vendor/DiligentEngine")
add_subdirectory("vendor/entt")
#add_subdirectory("vendor/glfw")
add_subdirectory("vendor/spdlog")
add_subdirectory("vendor/glm")


file(GLOB_RECURSE SRC "src/*.cpp" "src/*.h" "src/*.hpp" "vendor/DiligentEngine/DiligentTools/ThirdParty/imgui/backends/imgui_impl_glfw.h" "vendor/DiligentEngine/DiligentTools/ThirdParty/imgui/backends/imgui_impl_glfw.cpp")
add_library(Engine ${SRC})

target_precompile_headers(Engine PRIVATE "src/pch.hpp")

target_compile_options(Engine PRIVATE -DUNICODE -DENGINE_DLL)

target_include_directories(Engine PUBLIC "src")
target_include_directories(Engine PUBLIC "vendor/DiligentEngine/DiligentCore")
target_include_directories(Engine PUBLIC "vendor/DiligentEngine/DiligentFX")
target_include_directories(Engine PUBLIC "vendor/DiligentEngine/DiligentTools")
target_include_directories(Engine PUBLIC "vendor/entt/single_include")
target_include_directories(Engine PUBLIC "vendor/spdlog/include")
target_include_directories(Engine PUBLIC "vendor/glfw/include")
target_include_directories(Engine PUBLIC "vendor/glm")

target_link_libraries(Engine
    Diligent-GraphicsEngineD3D11-shared
    Diligent-GraphicsEngineOpenGL-shared
    Diligent-GraphicsEngineD3D12-shared
    Diligent-GraphicsEngineVk-shared

    Diligent-Imgui
)
target_link_libraries(Engine glfw)
target_link_libraries(Engine EnTT::EnTT)
target_link_libraries(Engine glm)

copy_required_dlls(Engine)

if(MSVC)
    macro(GroupSources curdir)

        file(GLOB children RELATIVE ${PROJECT_SOURCE_DIR}/${curdir} ${PROJECT_SOURCE_DIR}/${curdir}/*)

        foreach(child ${children})

            if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${curdir}/${child})

                GroupSources(${curdir}/${child})

            else()

                string(REPLACE "/" "\\" groupname ${curdir})

                # I would like to call the src root folder in a different name, only in visual studio (not mandatory requirement)

                string(REPLACE "src" "Common" groupname ${groupname})

                source_group(${groupname} FILES ${PROJECT_SOURCE_DIR}/${curdir}/${child})

            endif()

        endforeach()

    endmacro()

    GroupSources(src)
endif(MSVC)