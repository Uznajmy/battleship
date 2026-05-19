cmake_minimum_required(VERSION 3.10)
project(battleship)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(thirdparty/raylib)
add_subdirectory(thirdparty/raygui/projects/CMake)

file(GLOB INCLUDES "include/*.h" "include/*.hpp")
file(GLOB SOURCES "src/*.c" "src/*.cpp")

add_executable(battleship ${SOURCES} ${INCLUDES})
target_include_directories(battleship PRIVATE include)
target_link_libraries(battleship PRIVATE raylib raygui)
