#include "Log.h"

namespace HazelPVR {

    std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
    std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

    void Log::Init() {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        s_CoreLogger = spdlog::stdout_color_mt("HAZELPVR");
        s_CoreLogger->set_level(spdlog::level::trace);
        HZPVR_CORE_INFO("Initialised Core Logger!");

        s_ClientLogger = spdlog::stdout_color_mt("APP");
        s_ClientLogger->set_level(spdlog::level::trace);
        HZPVR_INFO("Initialised Client Logger!");
    }

} // HazelPVR
