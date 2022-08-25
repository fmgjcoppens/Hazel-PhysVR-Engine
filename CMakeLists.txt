#==================== PROJECT SETUP ====================
## General project settings
cmake_minimum_required(VERSION 3.23)
project(HazelPhysicsVREngine)
set(CMAKE_CXX_STANDARD 14)

## OS detection and related variables
include(OS_detection.cmake)

## User enabled definitions
set(USER_DEFINITIONS
#        HZPVR_ENABLE_ASSERTS
        )

## Toplevel name and project dirs
set(ENGINE_NAME     HazelPVR)   # Name used in all folder paths and targets
set(PLATFORM_NAME   Platform)   # Name of the folder for platform dependent source files
set(SRC_DIR         src)        # Source implementation files
set(INCL_DIR        include)    # Source definition files

## HazelPVR source & include dirs
set(ENGINE_SRC_DIR ${SRC_DIR}/${ENGINE_NAME})
set(ENGINE_INCL_DIR ${INCL_DIR}/${ENGINE_NAME})
set(PLATFORM_SRC_DIR ${SRC_DIR}/${PLATFORM_NAME})
set(PLATFORM_INCL_DIR ${INCL_DIR}/${PLATFORM_NAME})
set(VENDOR_INCL_DIR ${INCL_DIR}/vendor)

## Vendor (external dependencies) include dirs
# spdlog logger (submodule) include dir
set(LOGGER_INCL_DIR ${VENDOR_INCL_DIR}/spdlog/include)

# GLFW (submodule) build target and suppress building docs, tests and examples
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(include/vendor/glfw)

#==================== SRCS AND HEADERS TO TRACK ====================
# Precompiled header
set(PCH ${INCL_DIR}/hzpvrpch.h)

# HazelPVR sources and headers
file(GLOB ENGINE_SRCS
        ${ENGINE_SRC_DIR}/*.cpp)
file(GLOB ENGINE_HEADERS
        ${ENGINE_INCL_DIR}/*.h
        ${ENGINE_INCL_DIR}/Events/*.h)

# Platform sources and headers
file(GLOB_RECURSE PLATFORM_SRCS
        ${PLATFORM_SRC_DIR}/*.cpp)
file(GLOB_RECURSE PLATFORM_HEADERS
        ${PLATFORM_INCL_DIR}/*.h)

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
find_library(COCOA_LIB Cocoa)
find_library(OPENGL_LIB OpenGL)
find_library(IOKIT_LIB IOKit)
target_link_libraries(${ENGINE_NAME}
        glfw
        ${COCOA_LIB}
        ${OPENGL_LIB}
        ${IOKIT_LIB})

## Link SandboxApp with HazelPVR
target_link_libraries(SandboxApp
        ${ENGINE_NAME})
