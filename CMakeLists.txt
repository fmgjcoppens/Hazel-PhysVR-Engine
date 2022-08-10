cmake_minimum_required(VERSION 3.22)
project(HazelPhysVREngine)
set(CMAKE_CXX_STANDARD 14)

add_library(HazelPVR SHARED HazelPVR.cpp)
add_executable(HazelPVR_testApp main.cpp)

target_link_libraries(HazelPVR_testApp HazelPVR)