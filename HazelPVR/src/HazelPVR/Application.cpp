#include "hzpvrpch.hpp" // Precompiled header. Include not necessary with CMake

#include "HazelPVR/Application.hpp"
#include "HazelPVR/Renderer/Renderer.hpp"

#include <GLFW/glfw3.h>

namespace HazelPVR
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        HZPVR_CORE_ASSERT(!s_Instance, "Application already exists!");
        HZPVR_CORE_INFO("Creating new Application instance");
        s_Instance = this;

        m_Window = Scope<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(onEvent));

        Renderer::Init();

        // This can also be done in the Sandbox constructor (SandBoxApp.cpp) on the application side, but I chose to do it here because its
        // creation is not optional; if it's not created GLFW/ImGui will not initialize correctly!
        m_ImGuiLayer = std::make_shared<ImGuiLayer>();
        PushOverlay(m_ImGuiLayer);
    }

    Application::~Application()
    {
        HZPVR_INFO("Destroying Application instance");
    }

    void Application::PushLayer(Ref<Layer> layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Ref<Layer> layer)
    {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::onEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));

        HZPVR_CORE_TRACE("{0}", event);

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
        {
            (*--it)->OnEvent(event);
            if (event.Handled)
                break;
        }
    }

    void Application::Run()
    {
        while (m_Running)
        {
            float time = (float)glfwGetTime(); // Should go into Platform
            Timestep timestep = time - m_LastFrameRenderTime;
            m_LastFrameRenderTime = time;

            for (Ref<Layer> layer : m_LayerStack)
                layer->OnUpdate(timestep);

            m_ImGuiLayer->Begin();

            for (Ref<Layer> layer : m_LayerStack)
                layer->OnImGuiRender();

            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }

    void Application::Close()
    {
        m_Running = false;
    }

    bool Application::onWindowClose(WindowCloseEvent& event)
    {
        m_Running = false;
        return true;
    }
} // namespace HazelPVR
