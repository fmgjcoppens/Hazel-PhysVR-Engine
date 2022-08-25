#pragma once

#if defined HZPVR_PLATFORM_WINDOWS
    #ifdef HZPVR_BUILD_DLL
        #define HAZELPVR_API __declspec(dllexport)
    #else
        #define HAZELPVR_API __declspec(dllimport)
    #endif
#elif defined HZPVR_PLATFORM_MACOS
    #define HAZELPVR_API
#elif defined HZPVR_PLATFORM_LINUX
    #define HAZELPVR_API
#else
    #error "Unknown operating system!"
#endif


#ifdef HZPVR_ENABLE_ASSERTS
    #define HZPVR_ASSERT(x, ...) { if(!(x)) { HZPVR_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
    #define HZPVR_CORE_ASSERT(x, ...) { if(!(x)) { HZPVR_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define HZPVR_ASSERT(x, ...)
    #define HZPVR_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)
