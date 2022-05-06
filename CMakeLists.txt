cmake_minimum_required(VERSION 3.23)
project(Sandbox)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_subdirectory("Engine")

file(GLOB SRC "Sandbox/src/**.c" "Sandbox/src/**.cc" "Sandbox/src/**.cpp" "Sandbox/src/**.h" "Sandbox/src/**.hpp" "Sandbox/src/**.sc" )
add_executable(Sandbox ${SRC})

target_link_libraries(Sandbox Engine)

#add_custom_target(
#  get-data
#  COMMAND ${CMAKE_COMMAND} -E echo "$<TARGET_FILE:shaderc>"
#  COMMAND ${CMAKE_COMMAND} -E echo "${CMAKE_BINARY_DIR}"
#  VERBATIM
#)

#add_custom_target(
#    build-shaders
#    COMMAND $<TARGET_FILE:shaderc> -f ${CMAKE_CURRENT_SOURCE_DIR}/Sandbox/src/v_simple.sc -o ${CMAKE_BINARY_DIR}/v_simple.bin --type vertex -i ${CMAKE_CURRENT_SOURCE_DIR}/Engine/vendor/bgfx.cmake/bgfx/src --varyingdef ${CMAKE_CURRENT_SOURCE_DIR}/Sandbox/src/varying.def.sc -p vs_5_0 --disasm
#    COMMAND $<TARGET_FILE:shaderc> -f ${CMAKE_CURRENT_SOURCE_DIR}/Sandbox/src/f_simple.sc -o ${CMAKE_BINARY_DIR}/f_simple.bin --type fragment -i ${CMAKE_CURRENT_SOURCE_DIR}/Engine/vendor/bgfx.cmake/bgfx/src --varyingdef ${CMAKE_CURRENT_SOURCE_DIR}/Sandbox/src/varying.def.sc -p ps_5_0 --disasm
#  )

if (MSVC)
  set_property( DIRECTORY PROPERTY VS_STARTUP_PROJECT "Sandbox")
endif (MSVC)