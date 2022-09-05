#include "hzpvrpch.h" // Precompiled header. Include not necessary with CMake
#include "Application.h"

#include "Events/ApplicationEvent.h"

#include <glad/glad.h>

#include "Input.h"

namespace HazelPVR {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application* Application::s_Instance = nullptr;

    Application::Application() {
        HZPVR_CORE_ASSERT(!s_Instance, "Application already exists!");
        s_Instance = this;
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(onEvent));
     }

    Application::~Application() {
        HZPVR_INFO("Destroying instance of Application");
    }

    void Application::PushLayer(Layer* layer) {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer) {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::onEvent(Event& event) {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));

        HZPVR_CORE_TRACE("{0}", event);

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
            (*--it)->OnEvent(event);
            if (event.Handled) break;
        }

    }

    void Application::Run() {
        while (m_Running)
        {
//            glClearColor(0.0, 0.180392, 0.388235, 1); // Cool Black blue
            glClearColor(0.298039, 0.317647, 0.427451, 1); // Independence blue
            glClear(GL_COLOR_BUFFER_BIT);

            for (Layer* layer : m_LayerStack) layer->OnUpdate();

            m_Window->OnUpdate();
        }
    }

    bool Application::onWindowClose(WindowCloseEvent& event) {
        m_Running = false;
        return true;
    }

}