#include "hzpvrpch.h" // Precompiled header. Include not necessary with CMake
#include "Application.h"

#include "Events/ApplicationEvent.h"
#include <GLFW/glfw3.h>

namespace HazelPVR {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application::Application() {
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(onEvent));
    }

    Application::~Application() {
        HZPVR_INFO("Destroying instance of Application");
    }

    void Application::onEvent(Event& event) {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));
        HZPVR_CORE_TRACE("{0}", event);
    }

    void Application::Run() {
        while (m_Running)
        {
//            glClearColor(0.0, 0.180392, 0.388235, 1); // Cool Black blue
            glClearColor(0.298039, 0.317647, 0.427451, 1); // Independence blue
            glClear(GL_COLOR_BUFFER_BIT);
            m_Window->OnUpdate();
        }
    }

    bool Application::onWindowClose(WindowCloseEvent& event) {
        m_Running = false;
        return true;
    }

}