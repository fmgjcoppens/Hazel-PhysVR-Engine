cmake_minimum_required(VERSION 3.22)
project(HazelPhysVREngine)
set(CMAKE_CXX_STANDARD 14)

add_library(HazelPVRE SHARED HazelPVRE.cpp)
add_executable(HazelPVRE_testApp main.cpp)

target_link_libraries(HazelPVRE_testApp HazelPVRE)