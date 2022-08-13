cmake_minimum_required(VERSION 3.22)
project(HazelPhysVREngine)
set(CMAKE_CXX_STANDARD 14)

set(NAME HazelPVR)
set(SRC src)
set(INCL include)

set(HAZELPVR_SRC ${SRC}/${NAME})
set(HAZELPVR_INCL ${INCL}/${NAME})

set(HAZELPVR_HEADERS
        ${HAZELPVR_INCL}/Application.h
        ${HAZELPVR_INCL}/Core.h
        ${HAZELPVR_INCL}/EntryPoint.h)
set(HAZELPVR_SRCS
        ${HAZELPVR_SRC}/Core.cpp)

set(SANDBOX_HEADERS
        ${INCL}/HazelPVR.h
        ${HAZELPVR_INCL}/Application.h)
set(SANDBOX_SRCS
        src/SandboxApp.cpp
        src/HazelPVR/Application.cpp)

add_library(${NAME} SHARED ${HAZELPVR_SRCS} ${HAZELPVR_HEADERS})
target_include_directories(${NAME} PRIVATE ${HAZELPVR_INCL})

add_executable(SandboxApp ${SANDBOX_SRCS} ${SANDBOX_HEADERS})
target_include_directories(SandboxApp PRIVATE ${INCL} ${HAZELPVR_INCL})

target_link_libraries(SandboxApp ${NAME})