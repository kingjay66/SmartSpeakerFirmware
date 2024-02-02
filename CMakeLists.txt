cmake_minimum_required(VERSION 3.5)
project(ssf)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define the compiler
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

# Specify the output directory for the compiled binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

# Check if Clang-Tidy is available
if(CLANG_TIDY)
    find_program(CLANG_TIDY_COMMAND NAMES clang-tidy)
    if(CLANG_TIDY_COMMAND)
        # Set the clang-tidy checks, using your .clang-tidy configuration file
        set(CMAKE_CXX_CLANG_TIDY 
            "${CLANG_TIDY_COMMAND};--config-file=${CMAKE_SOURCE_DIR}/.clang-tidy")
    else()
        message(STATUS "clang-tidy not found")
    endif()
endif()

# Include directories
include_directories(include)

# Add the source files
add_executable(ssf
    src/GUI.cpp
    src/MusicPlayerGUI.cpp
    src/MusicPlayer.cpp
    src/Main.cpp
    src/User.cpp
    src/Speaker.cpp
    src/Settings.cpp
    src/NetworkService.cpp
    src/SettingsService.cpp
)

# Link libraries
target_link_libraries(ssf SDL2 SDL2_ttf curl)
