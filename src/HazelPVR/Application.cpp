#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace HazelPVR {

    Application::Application() {
        // Constructor implementation code
        HZPVR_CORE_INFO("HazelPVR::Application::Application() (CONSTRUCTOR)");
    }

    Application::~Application() {
        // Destructor implementation code
        HZPVR_CORE_INFO("HazelPVR::Application::~Application() (DESTRUCTOR)");
    }

    void Application::Run() {
        WindowResizeEvent e(1280, 720);
        if (e.IsInCategory(EventCategoryApplication)) {
            HZPVR_TRACE(e);
        }
        if (e.IsInCategory(EventCategoryInput)) {
            HZPVR_TRACE(e);
        }

        HZPVR_CORE_INFO("HazelPVR::Application::Run()");
        while (true);
    }

}