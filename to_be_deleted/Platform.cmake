## Platform detection
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(OS_NAME Linux)
    add_compile_definitions(HZPVR_PLATFORM_LINUX)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(OS_NAME macOS)
    add_compile_definitions(HZPVR_PLATFORM_MACOS)
    find_library(COCOA_LIB Cocoa)
    find_library(IOKIT_LIB IOKit)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(OS_NAME Windows)
    add_compile_definitions(HZPVR_PLATFORM_WINDOWS)
else()
    set(OS_NAME Unknown)
endif()

# Platform dir, sources and headers
set(PLATFORM_DIR Platform)   # Name of the folder for platform dependent source files

set(PLATFORM_SRC_DIR ${SRC_DIR}/${PLATFORM_DIR})
set(PLATFORM_INCL_DIR ${INCL_DIR}/${PLATFORM_DIR})

file(GLOB PLATFORM_SRCS
    ${PLATFORM_SRC_DIR}/${OS_NAME}/${OS_NAME}*.cpp
    ${PLATFORM_SRC_DIR}/OpenGL/*.cpp
)

file(GLOB PLATFORM_HEADERS
    ${PLATFORM_INCL_DIR}/${OS_NAME}/${OS_NAME}*.hpp
    ${PLATFORM_INCL_DIR}/OpenGL/*.hpp
)

# ## Some debug messages that could be useful
# message(STATUS "Value of OS_NAME: ${OS_NAME}")
# message(STATUS "Value of PLATFORM_SRCS: ${PLATFORM_SRCS}")
# message(STATUS "Value of PLATFORM_HEADERS: ${PLATFORM_HEADERS}")
# message(STATUS "Value of USER_DEFINITIONS: ${USER_DEFINITIONS}")
