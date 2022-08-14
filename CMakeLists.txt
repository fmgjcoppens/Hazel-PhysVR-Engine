cmake_minimum_required(VERSION 3.22)
project(HazelPhysVREngine)
set(CMAKE_CXX_STANDARD 14)

## Set some general names and dirs
set(ENGINE_NAME HazelPVR)
set(SRC_DIR src/)
set(INCL_DIR include/)
set(LIB_DIR lib/)

set(ENGINE_SRC_DIR ${SRC_DIR}/${ENGINE_NAME})
set(ENGINE_INCL_DIR ${INCL_DIR}/${ENGINE_NAME})

## Hazel dirs, headers and sources
set(ENGINE_HEADERS
        ${ENGINE_INCL_DIR}/Application.h
        ${ENGINE_INCL_DIR}/Core.h
        ${ENGINE_INCL_DIR}/EntryPoint.h)

set(ENGINE_SRCS ${ENGINE_SRC_DIR}/Core.cpp)
## Hazel dirs, headers and sources

## SandboxApp dirs, headers and sources
set(SANDBOX_HEADERS
        ${INCL_DIR}/HazelPVR.h
        ${ENGINE_INCL_DIR}/Application.h)

set(SANDBOX_SRCS
        ${SRC_DIR}/SandboxApp.cpp
        ${ENGINE_SRC_DIR}/Application.cpp)
## SandboxApp dirs, headers and sources


## Hazel build target
add_library(
        ${ENGINE_NAME} SHARED
        ${ENGINE_SRCS}
        ${ENGINE_HEADERS}
)

target_include_directories(
        ${ENGINE_NAME} PRIVATE
        ${ENGINE_INCL_DIR}
)
## Hazel build target

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
)
## SandboxApp build target

## Link SandboxApp and Hazel
target_link_libraries(SandboxApp ${ENGINE_NAME})
## Link SandboxApp and Hazel
