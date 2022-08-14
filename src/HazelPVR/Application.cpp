#include "../../include/HazelPVR/Application.h"

namespace HazelPVR {

    Application::Application() {
        // Constructor implementation code
        HZPVR_CORE_INFO("HazelPVR::Application::Application() (constructor)");
    }

    Application::~Application() {
        // Destructor implementation code
        HZPVR_CORE_INFO("HazelPVR::Application::~Application() (destructor)");
    }

    void Application::Run() {
        HZPVR_CORE_INFO("HazelPVR::Application::Run()");
//        while (true);
    }

}