#pragma once

#include "Core.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/ostr.h>

namespace HazelPVR {

    class HAZELPVR_API Log {
    public:
        static void Init();
        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };

} // HazelPVR

// Core log macros
#define HZPVR_CORE_TRACE(...)   ::HazelPVR::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HZPVR_CORE_INFO(...)    ::HazelPVR::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HZPVR_CORE_WARN(...)    ::HazelPVR::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HZPVR_CORE_ERROR(...)   ::HazelPVR::Log::GetCoreLogger()->error(__VA_ARGS__)

// Client log macros
#define HZPVR_TRACE(...)   ::HazelPVR::Log::GetClientLogger()->trace(__VA_ARGS__)
#define HZPVR_INFO(...)    ::HazelPVR::Log::GetClientLogger()->info(__VA_ARGS__)
#define HZPVR_WARN(...)    ::HazelPVR::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HZPVR_ERROR(...)   ::HazelPVR::Log::GetClientLogger()->error(__VA_ARGS__)
