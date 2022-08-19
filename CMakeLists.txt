#==================== PROJECT SETUP ====================
## General project settings
cmake_minimum_required(VERSION 3.23)
project(HazelPhysicsVREngine)
set(CMAKE_CXX_STANDARD 14)

## Toplevel name and project dirs
set(ENGINE_NAME HazelPVR)
set(SRC_DIR src/)
set(INCL_DIR include/)

## Hazel source & include dirs
set(ENGINE_SRC_DIR ${SRC_DIR}/${ENGINE_NAME})
set(ENGINE_INCL_DIR ${INCL_DIR}/${ENGINE_NAME})
set(VENDOR_INCL_DIR ${INCL_DIR}/vendor)

## Vendor (external) include dirs
# Logger include dir
set(LOGGER_INCL_DIR ${VENDOR_INCL_DIR}/spdlog/include/)

#==================== SRCS AND HEADERS TO TRACK ====================
# Hazel sources and headers
file(GLOB ENGINE_SRCS
        ${ENGINE_SRC_DIR}/*.cpp)
file(GLOB ENGINE_HEADERS
        ${ENGINE_INCL_DIR}/*.h
        ${ENGINE_INCL_DIR}/Events/*.h)

## SandboxApp sources and headers
set(SANDBOX_SRCS
        ${SRC_DIR}/SandboxApp.cpp)
set(SANDBOX_HEADERS
        ${INCL_DIR}/HazelPVR.h)

#==================== BUILD TARGETS ====================
## Hazel build target
add_library(
        ${ENGINE_NAME} SHARED
        ${ENGINE_SRCS}
        ${ENGINE_HEADERS}
)
target_include_directories(
        ${ENGINE_NAME} PRIVATE
        ${ENGINE_INCL_DIR}
        ${LOGGER_INCL_DIR}
)
target_precompile_headers(
        ${ENGINE_NAME} PRIVATE
        ${ENGINE_INCL_DIR}/hzpvrpch.h)

## SandboxApp build target
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
## Link SandboxApp and Hazel
target_link_libraries(SandboxApp ${ENGINE_NAME})
