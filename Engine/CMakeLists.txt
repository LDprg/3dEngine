cmake_minimum_required(VERSION 3.10)
project(Engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

file(GLOB_RECURSE SRC "src/*.cpp" "src/*.h" "src/*.hpp" )
add_executable(Engine ${SRC})