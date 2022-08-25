## OS detection
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
    set(UNIX_LIKE TRUE)
endif()

## Global compiler definitions
if(OS_NAME STREQUAL "Linux")
    #add_compile_definitions(HZPVR_PLATFORM_LINUX)
endif()
if(OS_NAME STREQUAL "macOS")
    add_compile_definitions(HZPVR_PLATFORM_MACOS)
endif()
if(OS_NAME STREQUAL "Windows")
    #add_compile_definitions(HZPVR_PLATFORM_WINDOWS)
endif()

