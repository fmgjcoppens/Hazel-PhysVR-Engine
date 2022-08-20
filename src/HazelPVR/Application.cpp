//#include "../hzpvrpch.h" // Precompiled header. Include not necessary with CMake
#include "Application.h"

#include "Events/ApplicationEvent.h"

#include <GLFW/glfw3.h>

namespace HazelPVR {

    Application::Application() {
        // Constructor implementation code
        HZPVR_CORE_TRACE("HazelPVR::Application::Application()");
    }

    Application::~Application() {
        // Destructor implementation code
        HZPVR_CORE_TRACE("HazelPVR::Application::~Application()");
    }

    void Application::Run() {

        WindowResizeEvent e(1280, 720);
        if (e.IsInCategory(EventCategoryApplication)) {
            HZPVR_TRACE(e);
        }
        if (e.IsInCategory(EventCategoryInput)) {
            HZPVR_TRACE(e);
        }

        int rc = glfwInit();
        HZPVR_CORE_TRACE(rc);

        while (true);
    }

}