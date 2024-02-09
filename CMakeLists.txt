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
    src/Main.cpp
    src/GUI/GUI.cpp
    src/GUI/Music/MusicPlayerGUI.cpp
    src/GUI/Music/MusicPlayer.cpp
    src/GUI/Video/VideoPlayerGUI.cpp
    src/GUI/Video/VideoPlayer.cpp
    src/Models/User.cpp
    src/Models/Speaker.cpp
    src/Models/Settings.cpp
    src/Services/NetworkService.cpp
    src/Services/SettingsService.cpp
)

# Directly set the path to the custom SDL2 library
set(CUSTOM_SDL2_LIBRARY "${CMAKE_SOURCE_DIR}/SDL2/build/.libs/libSDL2-2.0.so.0.2800.5")

# Link the custom SDL2 library
target_link_libraries(ssf "${CUSTOM_SDL2_LIBRARY}" SDL2_ttf curl)
