#==================== PROJECT SETUP ====================
## General project settings
cmake_minimum_required(VERSION 3.16)
project(HazelPVR LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

## Toplevel name and project dirs
set(ENGINE_NAME     HazelPVR)   # Name used in all folder paths and targets (same as proj name)
set(SRC_DIR         src)        # Source implementation files
set(INCL_DIR        include)    # Source definition files

## HazelPVR source & include dirs
set(ENGINE_SRC_DIR ${SRC_DIR}/${ENGINE_NAME})
set(ENGINE_INCL_DIR ${INCL_DIR}/${ENGINE_NAME})

## Project-wide user defines
add_compile_definitions(
        HZPVR_DEBUG
)

## Vendor specific (external dependencies)
include(Vendor.cmake)

## Detection and definition of platform specific paths and variables
include(Platform.cmake)

#==================== SRCS AND HEADERS TO TRACK ====================
# Precompiled headers
set(PCH ${INCL_DIR}/hzpvrpch.h)

# HazelPVR sources and headers
file(GLOB ENGINE_SRCS
        ${ENGINE_SRC_DIR}/*.cpp
        ${ENGINE_SRC_DIR}/ImGui/*.cpp
)

file(GLOB ENGINE_HEADERS
        ${ENGINE_INCL_DIR}/*.h
        ${ENGINE_INCL_DIR}/Events/*.h
        ${ENGINE_INCL_DIR}/ImGui/*.h
)

## Sandbox Application sources and headers
set(SANDBOX_SRCS
        ${SRC_DIR}/SandboxApp.cpp
)

set(SANDBOX_HEADERS
        ${INCL_DIR}/HazelPVR.h
)

#==================== BUILD TARGETS ====================
## The HazelPVR build target
# add_library(${ENGINE_NAME} SHARED
add_library(${ENGINE_NAME} STATIC
        ${ENGINE_SRCS}
        ${ENGINE_HEADERS}
        ${PLATFORM_SRCS}
        ${PLATFORM_HEADERS}
)

target_include_directories(${ENGINE_NAME} PRIVATE
        ${INCL_DIR}
        ${ENGINE_INCL_DIR}
        ${LOGGER_INCL_DIR}
        ${GLM_INCL_DIR}
        ${PLATFORM_INCL_DIR}
)

target_precompile_headers(
        ${ENGINE_NAME} PRIVATE ${PCH})

if(OS_NAME STREQUAL "macOS") # Cannot go to Platform.cmake because target does not exist there
    target_compile_definitions(${ENGINE_NAME} PRIVATE
            GL_SILENCE_DEPRECATION
    )
endif()
if(OS_NAME STREQUAL "Windows") # Cannot go to Platform.cmake because target does not exist there
    target_compile_definitions(${ENGINE_NAME} PRIVATE
            HZPVR_BUILD_DLL
            GLFW_INCLUDE_NONE
    )
endif()

## The SandboxApp build target
add_executable(SandboxApp
        ${SANDBOX_SRCS}
        ${SANDBOX_HEADERS}
)

target_include_directories(SandboxApp PRIVATE
        ${INCL_DIR}
        ${ENGINE_INCL_DIR}
        ${LOGGER_INCL_DIR}
        ${GLM_INCL_DIR}
)

#==================== LINKING ====================
## Link HazelPVR with dependencies
find_package(OpenGL REQUIRED)

target_link_libraries(${ENGINE_NAME}
        ${OPENGL_LIBRARIES}
        glfw
        glad
        imgui
)

if(OS_NAME STREQUAL "macOS") # Cannot go to Platform.cmake because target has to exist
    target_link_libraries(${ENGINE_NAME}
        ${COCOA_LIB}
        ${IOKIT_LIB}
    )
endif()

## Link SandboxApp with HazelPVR
target_link_libraries(SandboxApp ${ENGINE_NAME})
