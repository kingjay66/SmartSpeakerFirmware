cmake_minimum_required(VERSION 3.0)
project(ssf)

# Set the C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define the compiler
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

# Specify the output directory for the compiled binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

# Include directories
include_directories(include)

# Add the source files
add_executable(ssf
    src/Main.cpp
    src/User.cpp
    src/Speaker.cpp
    src/Settings.cpp
    src/NetworkService.cpp
    src/SettingsService.cpp
)

# Link libraries
target_link_libraries(ssf SDL2 curl)
