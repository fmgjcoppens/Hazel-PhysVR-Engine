cmake_minimum_required(VERSION 3.22)
project(HazelPhysVREngine)
set(CMAKE_CXX_STANDARD 14)

add_library(HazelPVR SHARED src/HazelPVR/Core.cpp)
add_executable(SandboxApp src/SandboxApp.cpp)

target_link_libraries(SandboxApp HazelPVR)