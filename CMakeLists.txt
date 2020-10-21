# Minimum version 3.0
cmake_minimum_required(VERSION 3.0)

# This project and version
project(GSG VERSION 0.0.1)

# Build target from sources.
configure_file(include/Config.in include/Config.hpp)

add_executable(GSG
	src/Main.cpp
	src/Engine.cpp
	src/Exception.cpp
	src/Logger.cpp
)

target_include_directories(GSG PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Linker.
target_link_libraries(GSG SDL2)
target_link_libraries(GSG SDL2_image)
target_link_libraries(GSG GL)
target_link_libraries(GSG GLU)
target_link_libraries(GSG GLEW)
