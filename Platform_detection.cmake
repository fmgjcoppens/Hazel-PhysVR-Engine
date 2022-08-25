## Platform detection
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(OS_NAME Linux)
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(OS_NAME macOS)
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(OS_NAME Windows)
endif()

if(OS_NAME STREQUAL "Linux" OR OS_NAME STREQUAL "Darwin")
    set(UNIX_LIKE TRUE)
endif()

## Some things are the same for macOS and Linux
if(OS_NAME STREQUAL "Linux" OR OS_NAME STREQUAL "Darwin")
    set(UNIX_LIKE TRUE) # Variable not used at the moment
endif()

## Global compiler definitions
if(OS_NAME STREQUAL "Linux")
    add_compile_definitions(HZPVR_PLATFORM_LINUX)
endif()
if(OS_NAME STREQUAL "macOS")
    add_compile_definitions(HZPVR_PLATFORM_MACOS)
endif()
if(OS_NAME STREQUAL "Windows")
    add_compile_definitions(HZPVR_PLATFORM_WINDOWS)
endif()

# Platform dir, sources and headers
set(PLATFORM_DIR Platform)   # Name of the folder for platform dependent source files
set(PLATFORM_SRC_DIR ${SRC_DIR}/${PLATFORM_DIR})
set(PLATFORM_INCL_DIR ${INCL_DIR}/${PLATFORM_DIR})

file(GLOB PLATFORM_SRCS
        ${PLATFORM_SRC_DIR}/${OS_NAME}/${OS_NAME}*.cpp)
file(GLOB PLATFORM_HEADERS
        ${PLATFORM_INCL_DIR}/${OS_NAME}/${OS_NAME}*.h)

#message(STATUS "Value of PLATFORM_SRCS: ${PLATFORM_SRCS}")
#message(STATUS "Value of PLATFORM_HEADERS: ${PLATFORM_HEADERS}")
