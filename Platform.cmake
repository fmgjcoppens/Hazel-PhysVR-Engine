## Platform detection
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(OS_NAME Linux)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(OS_NAME macOS)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(OS_NAME Windows)
else()
    set(OS_NAME Unknown)
endif()

## Global compiler definitions
if(OS_NAME STREQUAL "Linux")
    add_compile_definitions(HZPVR_PLATFORM_LINUX)
elseif(OS_NAME STREQUAL "macOS")
    add_compile_definitions(HZPVR_PLATFORM_MACOS)
    find_library(COCOA_LIB Cocoa)
    find_library(IOKIT_LIB IOKit)
elseif(OS_NAME STREQUAL "Windows")
    add_compile_definitions(HZPVR_PLATFORM_WINDOWS)
    set(USER_DEFINITIONS
            ${USER_DEFINITIONS}
            HZPVR_BUILD_DLL)
else()
    # Unsupported OS -> do nothing.
endif()

# Platform dir, sources and headers
set(PLATFORM_DIR Platform)   # Name of the folder for platform dependent source files
set(PLATFORM_SRC_DIR ${SRC_DIR}/${PLATFORM_DIR})
set(PLATFORM_INCL_DIR ${INCL_DIR}/${PLATFORM_DIR})

file(GLOB PLATFORM_SRCS
        ${PLATFORM_SRC_DIR}/${OS_NAME}/${OS_NAME}*.cpp)
file(GLOB PLATFORM_HEADERS
        ${PLATFORM_INCL_DIR}/${OS_NAME}/${OS_NAME}*.h)


# Some debug messages
message(STATUS "Value of OS_NAME: ${OS_NAME}")
message(STATUS "Value of PLATFORM_SRCS: ${PLATFORM_SRCS}")
message(STATUS "Value of PLATFORM_HEADERS: ${PLATFORM_HEADERS}")
message(STATUS "Value of USER_DEFINITIONS: ${USER_DEFINITIONS}")
