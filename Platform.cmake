## OS detection
if(CMAKE_SYSTEM_NAME STREQUAL Linux)
    add_compile_definitions(HZPVR_PLATFORM_LINUX)
elseif(CMAKE_SYSTEM_NAME STREQUAL Darwin)
    add_compile_definitions(HZPVR_PLATFORM_MACOS)
elseif(CMAKE_SYSTEM_NAME STREQUAL Windows)
    add_compile_definitions(HZPVR_PLATFORM_WINDOWS)
endif()