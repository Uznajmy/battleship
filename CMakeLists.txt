cmake_minimum_required(VERSION 3.10)
project(battleship)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(thirdparty/SDL)
add_subdirectory(thirdparty/SDL_ttf)
add_subdirectory(thirdparty/SDL_image)

file(GLOB INCLUDES "include/*.h" "include/*.hpp")
file(GLOB SOURCES "src/*.c" "src/*.cpp")

add_executable(battleship ${SOURCES} ${INCLUDES})
target_include_directories(battleship PRIVATE include)
target_link_libraries(battleship PRIVATE SDL3::SDL3 SDL3_ttf::SDL3_ttf SDL3_image::SDL3_image)
