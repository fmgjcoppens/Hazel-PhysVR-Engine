cmake_minimum_required(VERSION 3.16)
project(HazelPVREngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Global definitions
add_compile_definitions(
    HZPVR_DEBUG
)

# OS detection
include(DetectOs.cmake)

# Build HazelPVR lib
add_subdirectory(HazelPVR)

# Build the Sandbox app
add_subdirectory(Sandbox)