cmake_minimum_required(VERSION 3.16)
project(HazelPVREngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set global file structure
include(FileStructure.cmake)

# Platform detection
include(Platform.cmake)

# Build HazelPVR lib
add_subdirectory(${HAZELPVR})

# Build the Sandbox app
add_subdirectory(${SANDBOX})
