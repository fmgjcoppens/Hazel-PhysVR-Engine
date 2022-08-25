#==================== PROJECT SETUP ====================
## General project settings
cmake_minimum_required(VERSION 3.16)
project(HazelPhysicsVREngine LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)

## User enabled definitions
set(USER_DEFINITIONS
#        HZPVR_ENABLE_ASSERTS
#        HZPVR_ENABLE_RANDOM_DEFS
        )

## Toplevel name and project dirs
set(ENGINE_NAME     HazelPVR)   # Name used in all folder paths and targets
set(SRC_DIR         src)        # Source implementation files
set(INCL_DIR        include)    # Source definition files

## HazelPVR source & include dirs
set(ENGINE_SRC_DIR ${SRC_DIR}/${ENGINE_NAME})
set(ENGINE_INCL_DIR ${INCL_DIR}/${ENGINE_NAME})

## Detection and definition of platform specific paths and variables
include(Platform_detection.cmake)

## Vendor specific (external dependencies)
include(Vendor.cmake)

#==================== SRCS AND HEADERS TO TRACK ====================
# Precompiled headers
set(PCH ${INCL_DIR}/hzpvrpch.h)

# HazelPVR sources and headers
file(GLOB ENGINE_SRCS
        ${ENGINE_SRC_DIR}/*.cpp)
file(GLOB ENGINE_HEADERS
        ${ENGINE_INCL_DIR}/*.h
        ${ENGINE_INCL_DIR}/Events/*.h)

## Sandbox Application sources and headers
set(SANDBOX_SRCS
        ${SRC_DIR}/SandboxApp.cpp)
set(SANDBOX_HEADERS
        ${INCL_DIR}/HazelPVR.h)

#==================== BUILD TARGETS ====================
## The HazelPVR build target
add_library(
        ${ENGINE_NAME} SHARED
        ${ENGINE_SRCS}
        ${PLATFORM_SRCS}
        ${ENGINE_HEADERS}
        ${PLATFORM_HEADERS}
)
target_include_directories(
        ${ENGINE_NAME} PRIVATE
        ${INCL_DIR}
        ${ENGINE_INCL_DIR}
        ${PLATFORM_INCL_DIR}
        ${LOGGER_INCL_DIR}
)
target_precompile_headers(
        ${ENGINE_NAME} PRIVATE
        ${PCH}
)
target_compile_definitions(
        ${ENGINE_NAME} PRIVATE
        GL_SILENCE_DEPRECATION
        ${USER_DEFINITIONS}
)

## The SandboxApp build target
add_executable(
        SandboxApp
        ${SANDBOX_SRCS}
        ${SANDBOX_HEADERS}
)
target_include_directories(
        SandboxApp PRIVATE
        ${INCL_DIR}
        ${ENGINE_INCL_DIR}
        ${LOGGER_INCL_DIR}
)

#==================== LINKING ====================
## Link HazelPVR with dependencies
if(OS_NAME STREQUAL "macOS")
    find_library(COCOA_LIB Cocoa)
    find_library(IOKIT_LIB IOKit)
    target_link_libraries(${ENGINE_NAME}
            ${COCOA_LIB}
            ${IOKIT_LIB})
endif()
find_library(OPENGL_LIB OpenGL)
target_link_libraries(${ENGINE_NAME}
        glfw
        ${OPENGL_LIB})

## Link SandboxApp with HazelPVR
target_link_libraries(SandboxApp
        ${ENGINE_NAME})
