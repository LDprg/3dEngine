cmake_minimum_required(VERSION 3.10)
project(Engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory("vendor/DiligentEngine/DiligentCore")
add_subdirectory("vendor/DiligentEngine/DiligentFX")
add_subdirectory("vendor/DiligentEngine/DiligentTools")
add_subdirectory("vendor/entt")
add_subdirectory("vendor/glfw")
add_subdirectory("vendor/spdlog")
add_subdirectory("vendor/glm")

add_subdirectory("docs")

file(GLOB_RECURSE SRC "src/*.cpp" "src/*.hpp" "src/*.ixx")

if(MSVC)    
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /GR-")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
endif()

#add_library(Engine SHARED ${SRC})
add_library(Engine ${SRC})

target_precompile_headers(Engine PRIVATE "src/pch.hpp")

target_compile_options(Engine PUBLIC -DUNICODE -DENGINE_DLL)

target_include_directories(Engine PUBLIC "src")
target_include_directories(Engine PUBLIC "vendor/DiligentEngine/DiligentCore")
target_include_directories(Engine PUBLIC "vendor/DiligentEngine/DiligentFX")
target_include_directories(Engine PUBLIC "vendor/DiligentEngine/DiligentTools")
target_include_directories(Engine PUBLIC "vendor/entt/single_include")
target_include_directories(Engine PUBLIC "vendor/spdlog/include")
target_include_directories(Engine PUBLIC "vendor/glfw/include")
target_include_directories(Engine PUBLIC "vendor/glm")

target_link_libraries(Engine Diligent-Imgui)
target_link_libraries(Engine glfw)
target_link_libraries(Engine EnTT::EnTT)
target_link_libraries(Engine glm)

if (WIN32)
    add_compile_definitions(ENGINE_PLATFORM_WINDOWS
                            ENGINE_SUPPORT_D3D11
                            ENGINE_SUPPORT_D3D12
                            ENGINE_SUPPORT_OPENGL
                            ENGINE_SUPPORT_VULKAN)

    target_link_libraries(Engine
            Diligent-GraphicsEngineD3D12-shared
            Diligent-GraphicsEngineD3D11-shared
            Diligent-GraphicsEngineVk-shared
            Diligent-GraphicsEngineOpenGL-shared
            )
elseif(LINUX)
    add_compile_definitions(ENGINE_PLATFORM_LINUX
                            ENGINE_SUPPORT_OPENGL
                            ENGINE_SUPPORT_VULKAN)
    target_link_libraries(Engine
            Diligent-GraphicsEngineVk-shared
            Diligent-GraphicsEngineOpenGL-shared
            )
endif()

if (MSVC)
    copy_required_dlls(Engine)
endif(MSVC)

if(MSVC)
    macro(GroupSources curdir)

        file(GLOB children RELATIVE ${PROJECT_SOURCE_DIR}/${curdir} ${PROJECT_SOURCE_DIR}/${curdir}/*)

        foreach(child ${children})

            if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${curdir}/${child})

                GroupSources(${curdir}/${child})

            else()

                string(REPLACE "/" "\\" groupname ${curdir})

                # I would like to call the src root folder in a different name, only in visual studio (not mandatory requirement)

                string(REPLACE "src" "Source Files" groupname ${groupname})

                source_group(${groupname} FILES ${PROJECT_SOURCE_DIR}/${curdir}/${child})

            endif()

        endforeach()

    endmacro()

    GroupSources(src)
endif(MSVC)